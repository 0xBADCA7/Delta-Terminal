#ifndef PERSON_HPP
#define PERSON_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <time.h>
#include <cereal/types/string.hpp>

using namespace std;

#define MALE    true
#define FEMALE  false

extern vector<string> maleNames;
extern vector<string> femaleNames;
extern vector<string> surnames;
extern vector<string> countryCodes;

struct Person {
private:
	string generateIBAN();

	string generateIDNumber();

	string generateUniqueName(bool gender);

public:
	Person();

	string ID, name, IBAN;
	bool gender;

	template<class Archive>
	void serialize(Archive &archive) {
		archive(ID, name, IBAN, gender);
	}
};

bool loadCountryCodes();

bool loadNames();

#endif // PERSON_HPP
