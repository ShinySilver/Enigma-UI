//----lib header
#include "SerialControl.hpp"

//----standard libs
#include <iostream>
#include <chrono>		//tempos
#include <thread>

//----c libs
#include <termios.h>
#include <sys/stat.h>	//open parameters
#include <fcntl.h>		//open function
#include <unistd.h>		//write function


//----macros
//
#if DEBUG
#define DEBUG_MSG(str) do { std::cout << " >> DEBUG:" << str << '\n'; } while(false)
#else
#define DEBUG_MSG(str) do {} while(false)
#endif

#if ERROR
#define ERROR_MSG(str) do { std::cerr << " >> ERROR:" << str << '\n'; } while(false)
#else
#define ERROR_MSG(str) do {} while(false)
#endif


namespace SerialControl {

using namespace std::chrono_literals; //for easy time measuring


//----usefull variables for the lib inner workings

bool initialized = false;
char paths[][14] = {"/dev/ttyUSB00","/dev/ttyACM00"};


//----internal functions

int readMessage(int fd, char* data) {
	char byte;
	int n = 0;
	while(read(fd,&byte,1)>0 && byte != ';' && n<MAX_MESSAGE_SIZE) {
		data[n] = byte;
		n++;
	}
	if(n==MAX_MESSAGE_SIZE) return -1;
	data[n] = '\0';
	return n;
}


//----Module functions

std::string
Module::sendCommand(const std::string& cmd){

	this->moduleMutex_.lock();

	//TODO add support for commands longer than MAX_MESSAGE_SIZE
	const ssize_t size = cmd.size();
	const char* inData = cmd.c_str();

	//write to device, try WRITE_TRY_NB before giving up
	int i;
	for(i=0; write(this->fileDescriptor,inData,size) != size && i < WRITE_TRY_NB; i++) {}
	DEBUG_MSG("sending to " << this->name << " : " << cmd);
	if(i == WRITE_TRY_NB) {
		ERROR_MSG("could not write message to " << this->name);
		this->moduleMutex_.unlock();
		return WRITE_FAIL;
	}

	char data[MAX_MESSAGE_SIZE];
	const int n = readMessage(this->fileDescriptor,data);

	if(n>0) { 
		this->moduleMutex_.unlock();
		return std::string{data}; 
	}
	if(!n) {
		this->moduleMutex_.unlock();
		return std::string{NO_RESPONSE}; 
	}
	DEBUG_MSG("ccould not get message from " << this->name);

	this->moduleMutex_.unlock();
	return READ_FAIL;
}


int
Module::watch(void callback(const std::string& cmd)) {
	this->moduleMutex_.lock();

	this->callback = callback;

	this->moduleMutex_.unlock();
	return 0;
}


//----functions

std::vector<Module*> listModules(){
	moduleList.clear();
	std::vector<Module*> modules;

	//for each paths defined in hpp
	for(auto &elem: paths)	{

		//TODO add dynamic search of modules
		for(int i=0; i<=MAX_INDEX; i++) {

			if(i/10) {
				elem[11] = char(i/10 + '0');
				elem[12] = char(i%10 + '0');
			} else {
				elem[11] = char(i%10 + '0');
				elem[12] = '\0';
			}

			DEBUG_MSG(elem);

			//open file in R/W and without linking it to a terminal
			const int fd = open(elem, O_RDWR | O_NOCTTY);
			if(!fd) {
				DEBUG_MSG("could not open " << elem);
				continue;
			}

			//store default config to reapply it when communication end
			struct termios oldAttr;
			if(tcgetattr(fd, &oldAttr)) {
				DEBUG_MSG("could not get config for " << elem);
				continue;
			}

			//configuration, for more informations see
			//https://www.ibm.com/support/knowledgecenter/SSLTBW_2.1.0/com.ibm.zos.v2r1.bpxbd00/rttcsa.htm#rttcsa
			struct termios newAttr = oldAttr;
			cfsetispeed(&newAttr, BAUDRATE);
			cfsetospeed(&newAttr, BAUDRATE);
			cfmakeraw(&newAttr);
			newAttr.c_cflag &= ~HUPCL; 	//disable hang-up on close, otherwise the nanos reset themselves
			newAttr.c_cflag |= CS8;		//8 bits chars
			newAttr.c_cc[VMIN]  = 0; 	//number of chars read() wait for (0 means read() don't block)
			newAttr.c_cc[VTIME] = SERIAL_TIMEOUT;	//read timeout time (in 0.1 of secs)

			//apply previously set configuration to file
			if(tcsetattr(fd, TCSANOW, &newAttr)) {
				DEBUG_MSG("Could not apply config for " << elem);
				continue;
			}

			//clear the file
			tcflush(fd,TCIOFLUSH);

			if(write(fd,"whois;",6) != 6) {
				DEBUG_MSG("could not write whois message to " << elem);
				continue;
			}

			char data[MAX_MESSAGE_SIZE];
			if(readMessage(fd,data)<=0){
				DEBUG_MSG("could not get message from " << elem);
			}

			DEBUG_MSG("whois : " << data);
			moduleList.emplace_back(new Module(data,fd,oldAttr));	//store the module in a list
			modules.emplace_back(moduleList.back());	//get the module adress (moving adress issues ?)

		}

	}

	if(initialized) return modules;
	std::this_thread::sleep_for(1.5s);  //for nanos that struggle to respond the first time
	initialized = true;
	return listModules();
}


int update() {
	
	int nbResp = 0;

	for(const auto &elem: moduleList) {
		elem->moduleMutex_.lock();
		if(elem->callback) {
			char data[MAX_MESSAGE_SIZE];
			const int n = readMessage(elem->fileDescriptor,data);

			std::string tmp;
			if(n>0) tmp = std::string{data};
			else if(!n) {
				elem->moduleMutex_.unlock();
				continue;
			}
			else {
				tmp = READ_FAIL;
				ERROR_MSG("message to long from " << elem->name);
			}
			DEBUG_MSG("from " << elem->name << " : " << tmp);
			elem->callback(tmp);
		}
		elem->moduleMutex_.unlock();
	}

	return nbResp;
}


} //namespace SerialControl
