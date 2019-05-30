#ifndef SERIAL_CONTROL_HPP
#define SERIAL_CONTROL_HPP

//----standard libs
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <tuple>
#include <functional>
#include <mutex>

//----c libs
#include <termios.h>

namespace SerialControl {


//----configuration values (macros for now)

#define MAX_INDEX 10
#define MAX_MESSAGE_SIZE 256 //in number of chars
#define WRITE_TRY_NB 3 	//number of time SerialControl will retry in case of fail while writing
#define DEBUG 1
#define ERROR 1
#define BAUDRATE B2000000
#define WRITE_FAIL "sc_wf"
#define READ_FAIL "sc_rf"
#define NO_RESPONSE "sc_nr"
#define SERIAL_TIMEOUT 1 //read timeout time (in 0.1 of secs)


//----Module class

//I admit that aving an object here is not the most elegant, but, well... to borinng to fix
class Module {
	/**
	 * Correspond to a physical device, allow to send commands and monitor the responses
	 */

	public:

	std::string name;

	Module(const std::string name, const int fd, const struct termios oldAttr):
		name{name}, moduleMutex_{}, fileDescriptor{fd}, oldAttr{oldAttr} {}

	/**
	 * send a command to the device and check for a response
	 */
	std::string sendCommand(const std::string& cmd) const;
	/**
	 * set a lambda function that will be called in the update function when the device emit a message
	 */
	int watch(void callback(const std::string& cmd));

	private:
	mutable std::mutex *moduleMutex_;
	int fileDescriptor;
	struct termios oldAttr;
	std::function<void(std::string&)> callback;

	/**
 	* check all watched modules and execute the lambda associed
 	*/
	friend int update();

};


//----private variables

namespace {

	std::list<Module> moduleList;

}


//----functions

/**
 * Update the list of modules connected
 * return value : a list of the modules names (given by the modules)
 */
std::vector<Module*> listModules();

/**
 * Check for every module that has a callback if there is any message.
 * if there is, they will be passed to the callbakc function
 */
int update();

} //namespace SerialControl

#endif
