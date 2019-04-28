#include "SerialControl.hpp"

#include <iostream>
#include <vector>

int main() {

	auto modules = SerialControl::updateModules();
	for(const auto &elem: modules) {
		std::cout << elem << '\n';
	}
	for(const auto &elem: modules) {
		std::cout << elem << ": " << SerialControl::sendCommand("whois;",elem) << '\n';
}
	std::cout << "test" << ": " << SerialControl::sendCommand("whois;","test") << '\n';
	return 0;
}

