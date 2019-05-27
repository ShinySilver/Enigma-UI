#ifndef SERIAL_CONTROL_HPP
#define SERIAL_CONTROL_HPP

//----standard libs
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <tuple>
#include <functional>

//----c libs
#include <termios.h>

//----configuration values (macros until sby decide otherwise)
#define MAX_INDEX 10
#define MAX_MESSAGE_SIZE 256 //in number of chars
#define WRITE_TRY_NB 3 	//number of time SerialControl will retry in case of fail while writing
#define DEBUG 0
#define ERROR 1
#define BAUDRATE B2000000
#define WRITE_FAIL "sc_wf"
#define READ_FAIL "sc_rf"
#define NO_RESPONSE "sc_nr"
#define SERIAL_TIMEOUT 1 //read timeout time (in 0.1 of secs)

namespace SerialControl {

	/**
	 * A physical device, allow to send commands and to monitor the responses
	 */
	class Module {
		public:
			std::string name;

			Module(const std::string name, const int fd, const struct termios oldAttr):
				name{name}, fileDescriptor{fd}, oldAttr{oldAttr} {}

			/**
			 * send a command to the device and check for a response
			 */
			std::string sendCommand(const std::string& cmd) const;

			/**
			 * set a lambda function that will be called in the update function when the device emit a message
			 */
			int watch(void callback(const std::string& cmd));

		private:
			int fileDescriptor;
			struct termios oldAttr;
			std::function<void(std::string&)> callback;

		/**
	 	* check all watched modules and execute the lambda associed
	 	*/
		friend int update();

	};


	//----functions
	int update();
	/**
	 * Update the list of modules connected
	 * return value : a list of the modules names (given by the modules)
	 */
	std::vector<Module*> listModules();


	//----private variables
	namespace {
		std::list<Module> moduleList;
	}

} //namespace SerialControl

#endif
