#include "person.hpp"

vector<string> maleNames;
vector<string> femaleNames;
vector<string> surnames;
vector<string> countryCodes;

string Person::generateIBAN() {
	//TODO (Dylan #1 2015-08-10 ): Prevent Bank Account duplication
	stringstream s;
	s.str("");
	srand(time(0) + rand());
	s << countryCodes[rand() % countryCodes.size()];

	int i = rand() % 99 + 1;

	i > 9 ? s << i << " " : s << "0" << i << " ";
	for (int i = 0; i < 4; i++)
		rand() % 2 == 1 ? s << (char) (rand() % 26 + 65) : s << rand() % 10;
	s << " ";
	// 13 if number is too long, 21 if realistic
	for (int i = 1; i < 13; i++) {
		s << rand() % 10;
		if (i % 4 == 0)
			s << " ";
	}
	return s.str();
}

string Person::generateIDNumber() {
	//TODO (Dylan #1 2015-08-10 ): Prevent ID duplication
	stringstream s;
	s.str("");
	srand(time(0) + rand());
	int first, second, third;
	first = second = third = 1;

	while (true) {
		first = rand() % 899 + 1;
		if (first != 666)
			break;
	}

	second = rand() % 99 + 1;
	third = rand() % 9999 + 1;
	first > 99 ? s << first << "-" : first > 9 ? s << "0" << first << "-" : s << "00" << first << "-";
	second > 9 ? s << second << "-" : s << "0" << second << "-";
	third > 999 ? s << third : third > 99 ? s << "0" << third : third > 9 ? s << "00" << third : s << "000" << third;
	return s.str();
}

string Person::generateUniqueName(bool gender) {
	//TODO (Dylan #1 2015-08-10 ): Prevent Name duplication
	stringstream s;
	s.str("");
	srand(time(0) + rand());
	gender ? s << maleNames[rand() % maleNames.size()] << " " << surnames[rand() % surnames.size()] :
	s << femaleNames[rand() % femaleNames.size()] << " " << surnames[rand() % surnames.size()];
	return s.str();
}

Person::Person() {
	gender = rand() % 2 == 1 ? MALE : FEMALE;
	name = generateUniqueName(gender);
	ID = generateIDNumber();
	IBAN = generateIBAN();
};

bool loadCountryCodes() {
	ifstream readFile;
	readFile.open("Data/Country Codes");
	if (!readFile)
		return false;

	while (readFile) {
		string s;
		readFile >> s;
		if (s.length() > 0)
			countryCodes.push_back(s);
	}
	readFile.close();
	return true;
}

bool loadNames() {
	ifstream readFile;
	readFile.open("Data/Male Names");
	if (!readFile)
		return false;

	while (readFile) {
		string name;
		readFile >> name;
		if (name.length() > 0)
			maleNames.push_back(name);
	}
	readFile.close();

	readFile.open("Data/Female Names");
	if (!readFile) return false;
	while (readFile) {
		string name;
		readFile >> name;
		if (name.length() > 0)
			femaleNames.push_back(name);
	}
	readFile.close();

	readFile.open("Data/Surnames");
	if (!readFile)
		return false;

	while (readFile) {
		string name;
		readFile >> name;
		if (name.length() > 0)
			surnames.push_back(name);
	}
	readFile.close();
	random_shuffle(maleNames.begin(), maleNames.end());
	random_shuffle(femaleNames.begin(), femaleNames.end());
	random_shuffle(surnames.begin(), surnames.end());
	return true;
}

