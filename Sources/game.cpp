#include "game.hpp"
#include "menus.hpp"

#define GAMESAVEROOT "Save/GameData/"

#define COMPANYSTARTAMOUNT 500
#define PEOPLESTARTAMOUNT 10000

template<typename T>
bool saveFile(string file, T &x) {
	ofstream f(string(GAMESAVEROOT) + file, fstream::binary);
	try {
		cereal::BinaryOutputArchive oarchive(f);
		oarchive(x);
	}
	catch (cereal::Exception) {
		return false;
	}
	return true;
}

template<typename T>
bool loadFile(string file, T &x) {
	ifstream f(string(GAMESAVEROOT) + file, fstream::binary);
	try {
		cereal::BinaryInputArchive iarchive(f);
		iarchive(x);
	}
	catch (cereal::Exception) {
		return false;
	}
	return true;
}

void GameEngine::init() {
	//TODO (Dylan #1 2015-09-23): Initialise Game world
	//TODO (Dylan #1 2015-09-23): Generate Computer systems and security measures for each
	auto load = [&](int &progress) {
		mtx.lock();
		progress = 0;
		mtx.unlock();
		bool status = true;
		int stages = 2, step = 100 / stages;
		// Begin Stages
		if (!loadFile("Companies", gameEngine.worldCompanies))
			for (int i = 0; i < COMPANYSTARTAMOUNT; i++)
				gameEngine.worldCompanies.push_back(Company());
		mtx.lock();
		progress += step;
		mtx.unlock();
		if (!loadFile("People", gameEngine.worldPeople))
			for (int i = 0; i < PEOPLESTARTAMOUNT; i++)
				gameEngine.worldPeople.push_back(Person());
		mtx.lock();
		progress += step;
		mtx.unlock();
		return status;
	};
	saveLoadScreen("Loading", load);
}

int game() {
	gameEngine.init();
	UITaskBar taskBar;

	sf::Text text("", Font, MENU_FONT_SIZE), text2("", Font, MENU_FONT_SIZE);
	text.setStyle(sf::Text::Bold);
	text2.setStyle(sf::Text::Bold);
	text2.setPosition(text.getPosition().x, text.getPosition().y + 100);

	if (gameEngine.worldCompanies.size() > 0)
		text.setString(gameEngine.worldCompanies[0].Name + ", " + gameEngine.worldCompanies[0].system.IP);
	else text.setString("Empty");

	if (gameEngine.worldPeople.size() > 0)
		text2.setString(gameEngine.worldPeople[0].name);
	else text2.setString("Empty");

	auto save = [&](int &progress) {
		mtx.lock();
		progress = 0;
		mtx.unlock();

		bool status = true;
		int stages = 3, step = 100 / stages;

		auto updateProgress = [&] {
			mtx.lock();
			progress += step;
			mtx.unlock();
		};

		saveFile("Companies", gameEngine.worldCompanies);
		updateProgress();

		saveFile("People", gameEngine.worldPeople);
		updateProgress();

		return status;
	};

	auto saveScreen = [&] {
		saveLoadScreen("Saving", save);
		throw -1;
	};

	map<sf::Event::EventType, function<void(void) >> gameEvents = {
			make_pair(
					Event.Closed,
					[&] {
						saveScreen();
						saveAndQuit();
					}
			),
			make_pair(
					Event.MouseButtonPressed,
					[&] {
						for (int i = 0; i < taskBar.MAXBUTTONS; i++)
							if (taskBar[i].first.getGlobalBounds().contains(mapPixelToCoords(Event.mouseButton)))
								taskBar[i].second();
					}
			),
			make_pair(
					Event.KeyPressed,
					[&] {
						if (Event.key.code == sf::Keyboard::Escape) {
							pauseMenu();
							if (gameEngine.gameQuit && gameEngine.appQuit) {
								saveScreen();
								saveAndQuit();
							} else if (gameEngine.gameQuit && !gameEngine.appQuit) {
								saveScreen();
								throw (-1);
							}
						}
					}
			)
	};

	taskBar[taskBar.Quit].second = gameEvents[Event.KeyPressed];

	while (App.isOpen()) {
		while (App.pollEvent(Event)) {
			for (int i = sf::Event::EventType::Closed; i < sf::Event::EventType::Count; i++) {
				if (Event.type == (sf::Event::EventType) i && gameEvents.count((sf::Event::EventType) i) == 1) {
					try {
						gameEvents[Event.type]();
					}
					catch (int p) {
						return 0;
					}
				}
			}
		}
		App.clear();
		App.draw(Background);
		App.draw(taskBar);
		App.draw(text);
		App.draw(text2);
		App.display();
	}
	return -1;
}
