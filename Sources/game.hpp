#ifndef GAME_HPP
#define GAME_HPP

#include "person.hpp"
#include "company.hpp"

#include "progressModule.hpp"
#include "gameUI.hpp"
#include "resources.hpp"
#include "utilFunctions.hpp"
#include "includes.hpp"
#include "defines.hpp"
#include "save.hpp"

#include <iterator>
#include <algorithm>
#include <functional>
#include <thread>
#include <string>
#include <vector>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>


struct GameEngine {
	void init();

	double version;
	bool gameQuit = false;
	bool appQuit = false;

	vector<Company> worldCompanies;
	vector<Person> worldPeople;

	template<class Archive>
	void serialize(Archive &ar) {
		ar(
				CEREAL_NVP(version),
				CEREAL_NVP(worldCompanies),
				CEREAL_NVP(worldPeople)
		);
	}
};

extern GameEngine gameEngine;

int game();

#endif // GAME_HPP

