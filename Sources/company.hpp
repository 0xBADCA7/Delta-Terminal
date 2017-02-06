#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "computerSystem.hpp"

using namespace std;

extern vector<string> companyNames;
extern vector<string> companySuffixes;

struct Company {
public:
	Company();

	string Name;
	ComputerSystem system;

	template<class Archive>
	void serialize(Archive &archive) {
		archive(Name, system);
	}
};

bool loadCompanyNames();

string generateCompanyName();

#endif // COMPANY_HPP

