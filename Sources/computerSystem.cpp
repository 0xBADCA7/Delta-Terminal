#include "computerSystem.hpp"

string generateIP() {
	stringstream s;
	s << rand() % 255 + 1 << "." << rand() % 255 + 1 << "." << rand() % 255 + 1 << "." << rand() % 255 + 1;
	return s.str();
}

ComputerSystem::ComputerSystem() {
	IP = generateIP();
}
