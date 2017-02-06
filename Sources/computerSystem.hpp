#ifndef COMPUTER_SYSTEM_HPP
#define COMPUTER_SYSTEM_HPP

#include "includes.hpp"

struct Log {
	//TODO (Dylan #1 2015-12-17 ): Logs
	bool nothing;

	template<class Archive>
	void serialize(Archive &archive) {
		archive(nothing);
	}
};

struct ComputerSystem {
	ComputerSystem();

	sf::Vector2f Coords;
	string IP;
	sf::RectangleShape mapNode;

	vector<Log> Logs;

	template<class Archive>
	void serialize(Archive &archive) {
		archive(
				Coords,
				IP,
				Logs
		);
	}

};

string generateIP();


#endif // COMPUTER_SYSTEM_HPP

