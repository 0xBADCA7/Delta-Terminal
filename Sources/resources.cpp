#include "includes.hpp"
#include "defines.hpp"
#include "resources.hpp"
#include "company.hpp"
#include "person.hpp"
#include "textureManager.hpp"
#include "progressModule.hpp"
#include "audio.hpp"
#include "taurusFont.hpp"

#include <dirent.h>


void resourceInit() {
	auto load = [&](int &progress) {
		mtx.lock();
		progress = 0;
		mtx.unlock();

		bool status = true;
		int stages = 6, step = 100 / stages;

		auto updateProgress = [&] {
			mtx.lock();
			progress += step;
			mtx.unlock();
		};

		//NOTE Fonts Loaded Here
		if (!Font.loadFromMemory(taurusFont, taurusFont_size))
			exit((int) RESOURCE_ERROR_CODE::FontError); // You're screwed if this fails
		if (!CleanFont.loadFromFile("Fonts/SourceCodePro.ttf"))
			throw ((int) RESOURCE_ERROR_CODE::FontError);

		updateProgress();

		//NOTE Data Loaded Here
		if (!loadCompanyNames())
			throw ((int) RESOURCE_ERROR_CODE::DataError);
		if (!loadCountryCodes())
			throw ((int) RESOURCE_ERROR_CODE::DataError);
		if (!loadNames())
			throw ((int) RESOURCE_ERROR_CODE::DataError);
		updateProgress();

		//NOTE Sounds Loaded Here
		if (!loadSound("button", "Audio/Button.wav"))
			throw ((int) RESOURCE_ERROR_CODE::AudioError);
		updateProgress();

		DIR *directory;
		dirent *entry;

		if ((directory = opendir(MUSIC_DIRECTORY)) != NULL) {
			while ((entry = readdir(directory)) != NULL) {
				string name(entry->d_name);
				if (name == "." || name == "..")
					continue;

				vector<string> extensions =
						{"ogg", "wav", "flac", "aiff", "au", "raw", "paf", "svx", "nist", "voc", "ircam", "w64",
						 "mat4", "mat5 pvf", "htk", "sds", "avr", "sd2", "caf", "wve", "mp	c2k", "rf64"
						};
				for (auto i : extensions) {
					if (name.find("." + i) != string::npos) {
						Songs.push_back(name);
						break;
					}
				}
			}
			closedir(directory);
		} else throw ((int) RESOURCE_ERROR_CODE::AudioError);
		updateProgress();

		currentSong = 0;
		srand(time(0) + rand());
		random_shuffle(Songs.begin(), Songs.end());
		if (Songs.size() > 0)
			if (!music.openFromFile(string(MUSIC_DIRECTORY) + Songs[currentSong]))
				throw ((int) RESOURCE_ERROR_CODE::AudioError);
		updateProgress();

		//NOTE Textures Loaded Here
		if (!textureManager.loadTexture("Background", "Graphics/Continents.png"))
			throw ((int) RESOURCE_ERROR_CODE::GraphicsError);
		if (!textureManager.loadTexture("UIButton-Programs", "Graphics/UI/UIButton-Programs-01.png"))
			throw ((int) RESOURCE_ERROR_CODE::GraphicsError);
		if (!textureManager.loadTexture("UIButton-Quit", "Graphics/UI/UIButton-Quit-01.png"))
			throw ((int) RESOURCE_ERROR_CODE::GraphicsError);
		if (!textureManager.loadTexture("UIButton-PC", "Graphics/UI/UIButton-PC-01.png"))
			throw ((int) RESOURCE_ERROR_CODE::GraphicsError);
		if (!textureManager.loadTexture("UIButton-Media", "Graphics/UI/UIButton-Media-01.png"))
			throw ((int) RESOURCE_ERROR_CODE::GraphicsError);

		Background.setTexture(textureManager["Background"]);
		updateProgress();

		return status;
	};
	saveLoadScreen("Loading", load);
	thread musicManager([&]() {
		while (true) {
			if (settings.audio.musicEnabled && music.getStatus() == sf::Music::Stopped)
				if (!nextSong())
					return 0;
			this_thread::sleep_for(chrono::seconds(3));
		}
		return 0;
	});
	musicManager.detach();
}

void setGlobalVolume() {
	for (auto &i : soundManager)
		i.second.second.setVolume(settings.audio.soundVolume);
	music.setVolume(settings.audio.musicVolume);
}

void instanciateWindow() {
	if (settings.graphics.fullscreenEnabled)
		App.create(settings.graphics.VideoMode, GAMENAME, sf::Style::Fullscreen);
	else App.create(settings.graphics.VideoMode, GAMENAME, sf::Style::Close);
	View.setSize(APP_WIDTH, APP_HEIGHT);
	View.setCenter(APP_WIDTH / 2, APP_HEIGHT / 2);
	App.setView(View);
	App.setFramerateLimit(30);
	App.setActive(true);
}

sf::Vector2f mapPixelToCoords(sf::Event::MouseButtonEvent &pos) {
	return App.mapPixelToCoords(sf::Vector2i(pos.x, pos.y));
}
