#include <iostream>
#include <exception>

#include "SerialControl.hpp"

#define MAX_INDEX 10
#define TIMEOUT 10

namespace SerialControl {

std::vector<std::string> updateModules(){

	std::vector<std::string> moduleNames;

	// For each USB module connected...
	for(int i=0; i<=MAX_INDEX; i++) {
		std::string path = "/dev/ttyACM" + std::to_string(i);
		std::fstream file;

		// Open connection
		file.open(path, std::ios_base::in|std::ios_base::out);
		if(file.fail()) { if(DEBUG) std::cerr << "unable to open " << path << '\n'; }

		// Send name request
		file << "whois;" << std::endl;

		// Receive name request response
		std::string response;
		file >> response;

		// Si un fichier correspondant à un périphérique est trouvé...
		if(!file.fail()) {
			// .. alors on l'ajoute à la liste privèe des modules
			Module mod = {false, i, response};
			moduleList.emplace_back(mod);
			moduleNames.emplace_back(response);
		}

		// On clot le flux de fichier
		file.close();
	}
	return moduleNames;
}

std::string sendCommand(const std::string& cmd, const std::string& mod) {
	for(auto &elem: moduleList) {
		if(elem.name == mod) {
			std::fstream file;

			// Open connection
			file.open("/dev/ttyACM0" + std::to_string(elem.id), std::ios_base::in|std::ios_base::out);
			if(file.fail()) {
				if(DEBUG) std::cerr << "unable to open communication with " << mod << '\n';
				return "no response";
			}

			// Send command
			file << cmd << std::endl;

			// Receive response
			std::string response;
			//file >> response;

			//end communication
			file.close();
			return response;
		}
	}
	return "no_response";
}


int registerEmittingModule(const std::string& moduleName) {
	for(auto &elem: moduleList) {
		if(elem.name == moduleName) {
			elem.watch = true;
			return 0;
		}
	}
	return 1;
}


std::vector<SerialMessage> readAll() {
	std::vector<SerialMessage> output;
	for(auto &elem: moduleList) {
		if(elem.watch) {
			std::fstream file;
			file.open("/dev/ttyACM" + std::to_string(elem.id), std::ios_base::in);
			if(file.fail()) {
				std::cerr << "unable to open communication with " << elem.name << '\n';
				continue;
			}
			if(isEmpty(file)){
				file.close();
				continue;
			}
			std::string response;
			file >> response;
			output.emplace_back(SerialMessage{elem.name,response});
		}
	}
	return output;
}


} //namespace SerialControl
