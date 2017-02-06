#include "company.hpp"

vector<string> companyNames;
vector<string> companySuffixes;

bool loadCompanyNames() {
	ifstream readFile;
	readFile.open("Data/Company Names");

	if (!readFile)
		return false;

	while (readFile) {
		string s;
		readFile >> s;
		if (s.length() > 0) companyNames.push_back(s);
	}
	readFile.close();

	readFile.open("Data/Company Suffixes");
	if (!readFile)
		return false;

	while (readFile) {
		string s;
		readFile >> s;
		if (s.length() > 0)
			companySuffixes.push_back(s);
	}
	readFile.close();
	//    random_shuffle(companyNames.begin(), companyNames.end());
	//    random_shuffle(companySuffixes.begin(), companySuffixes.end());
	return true;
}

string generateCompanyName() {
	stringstream s;
	if (companyNames.size() > 0 && companySuffixes.size() > 0) {
		s << companyNames[rand() % companyNames.size()] << " ";
		s << companySuffixes[rand() % companySuffixes.size()];
	}
	return s.str();
}

Company::Company() {
	Name = generateCompanyName();
}
