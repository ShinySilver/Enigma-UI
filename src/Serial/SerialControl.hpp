
#ifndef SERIAL_CONTROL_HPP
#define SERIAL_CONTROL_HPP

#include <string>
#include <vector>
#include <fstream>
#include <tuple>

#define MAX_INDEX 10
#define TIMEOUT 10
#define DEBUG 1

namespace SerialControl {

	typedef struct{
		std::string sender;
		std::string message;
	} SerialMessage;

	/**
	 * Update the list of modules connected
	 * return value : a list of the modules names (given by the modules)
	 */
	std::vector<std::string> updateModules();

	/**
	 * Send a command to the specified module
	 */
	std::string sendCommand(const std::string& cmd, const std::string& mod);

	/**
	 * Set a watch flag on the specified module so that it output will be checked
	 * at each update
	 */
	int registerEmittingModule(const std::string& moduleName);

	/**
	 * Check all watched modules and return a list of all the reponses. It is
	 * intended to be used in a kind of event handler/exception handler
	 */
	std::vector<SerialMessage> readAll();

	namespace {
		typedef struct {
			bool watch = false;
			const int id = 0;
			const std::string name = "no_device";
		} Module;
		bool isEmpty(std::fstream& file) {
	    	return file.peek() == std::fstream::traits_type::eof();
		}
		std::vector<Module> moduleList;
	}
}

#endif
