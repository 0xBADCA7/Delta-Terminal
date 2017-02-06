#include "includes.hpp"
#include "defines.hpp"
#include "dynamicMenu.hpp"
#include "menus.hpp"
#include "utilFunctions.hpp"
#include "audio.hpp"
#include "resources.hpp"

int optionsMenu() {
	Menu menu;
	menu.setTitle("Options");

	struct Buttons {
		enum {
			GraphicsOptions,
			MusicVolume,
			SoundVolume,
			MusicToggle,
			SoundToggle,
			Back,
		};
	};

	sf::RectangleShape musicVolumeBar(sf::Vector2f(400, 10));
	sf::RectangleShape musicVolumeSlider(sf::Vector2f(24, 30));

	menu.newButton("Graphics Options").setFillColour(sf::Color::Transparent).setTextColour(sf::Color::White) =
			[&] {
				menu.subMenuEntered = true;
				graphicsOptionsMenu();
			};

	menu.newButton("Music Volume : " + toString(settings.audio.musicVolume)).mimicStyles(
			menu[Buttons::GraphicsOptions]) =
			[&] {
				if (settings.audio.musicVolume == 0)
					settings.audio.musicVolume = 100;
				else if (settings.audio.musicVolume == 100)
					settings.audio.musicVolume = 0;
				else settings.audio.musicVolume = 100;

				musicVolumeSlider.setPosition(musicVolumeBar.getPosition().x + (settings.audio.musicVolume * 4) - 12,
				                              musicVolumeBar.getPosition().y - (10));
				menu[Buttons::MusicVolume].setString("Music Volume : " + toString((int) settings.audio.musicVolume));
				setGlobalVolume();
			};

	musicVolumeBar.setFillColor(sf::Color::Green);
	musicVolumeBar.setOutlineColor(sf::Color::Black);
	musicVolumeBar.setOutlineThickness(2);
	musicVolumeBar.setPosition(700, menu[Buttons::MusicVolume].getPosition().y + 20);

	musicVolumeSlider.setFillColor(sf::Color(0, 150, 0));
	musicVolumeSlider.setOutlineColor(sf::Color::Black);
	musicVolumeSlider.setOutlineThickness(2);
	musicVolumeSlider.setPosition(musicVolumeBar.getPosition().x + (settings.audio.musicVolume * 4) - 12,
	                              musicVolumeBar.getPosition().y - (10));

	sf::RectangleShape soundVolumeBar = musicVolumeBar;
	sf::RectangleShape soundVolumeSlider = musicVolumeSlider;

	menu.newButton("Sound Volume : " + toString(settings.audio.soundVolume)).mimicStyles(
			menu[Buttons::GraphicsOptions]) = [&] {
		if (settings.audio.soundVolume == 0) {
			settings.audio.soundVolume = 100;
			soundManager["button"].second.play();
		} else if (settings.audio.soundVolume == 100)
			settings.audio.soundVolume = 0;
		else settings.audio.soundVolume = 100;

		soundVolumeSlider.setPosition(soundVolumeBar.getPosition().x + (settings.audio.soundVolume * 4) - 12,
		                              soundVolumeBar.getPosition().y - (10));
		menu[Buttons::SoundVolume].setString("Sound Volume : " + toString((int) settings.audio.soundVolume));
		setGlobalVolume();
	};

	soundVolumeBar.setPosition(700, menu[Buttons::SoundVolume].getPosition().y + 20);

	soundVolumeSlider.setPosition(soundVolumeBar.getPosition().x + (settings.audio.soundVolume * 4) - 12,
	                              soundVolumeBar.getPosition().y - (10));

	menu.newButton("Music : " + toString(settings.audio.musicEnabled)).mimicStyles(
			menu[Buttons::GraphicsOptions]) =
			[&] {
				settings.audio.musicEnabled = !settings.audio.musicEnabled;
				menu[3].setString("Music : " + toString(settings.audio.musicEnabled));
				if (!settings.audio.musicEnabled && music.getStatus() == sf::Music::Playing)
					music.stop();
				else if (settings.audio.musicEnabled)
					music.play();
			};

	menu.newButton("Sound : " + toString(settings.audio.soundEnabled)).mimicStyles(
			menu[Buttons::GraphicsOptions]) =
			[&] {
				settings.audio.soundEnabled = !settings.audio.soundEnabled;
				if (settings.audio.soundEnabled)
					soundManager["button"].second.play();
				menu[4].setString("Sound : " + toString(settings.audio.soundEnabled));
			};

	menu.newButton("Back", 50, 1080 - (Font.getLineSpacing(MENU_FONT_SIZE * 2 + 20)))
			.mimicStyles(menu[Buttons::GraphicsOptions]) = [&] { throw (0); };

	while (App.isOpen()) {
		while (App.pollEvent(Event)) {
			for (int i = sf::Event::EventType::Closed; i < sf::Event::EventType::Count; i++) {
				if (Event.type == (sf::Event::EventType) i && menu.eventManager.count((sf::Event::EventType) i) == 1) {
					try {
						menu.eventManager[Event.type]();
					}
					catch (int p) {
						return 0;
					}
				}
			}

			if (musicVolumeBar.getGlobalBounds().contains(
					mapPixelToCoords(sf::Mouse::getPosition(App)).x,
					mapPixelToCoords(sf::Mouse::getPosition(App)).y) &&
			    sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				musicVolumeSlider.setPosition(mapPixelToCoords(sf::Mouse::getPosition(App)).x - 12,
				                              musicVolumeSlider.getPosition().y);
				settings.audio.musicVolume =
						(int) (musicVolumeSlider.getPosition().x - musicVolumeBar.getPosition().x + 12) / 4;
				menu[Buttons::MusicVolume].setString("Music Volume : " + toString((int) settings.audio.musicVolume));
				setGlobalVolume();
			}

			if (soundVolumeBar.getGlobalBounds().contains(
					mapPixelToCoords(sf::Mouse::getPosition(App)).x,
					mapPixelToCoords(sf::Mouse::getPosition(App)).y)
			    && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				soundVolumeSlider.setPosition(mapPixelToCoords(sf::Mouse::getPosition(App)).x - 12,
				                              soundVolumeSlider.getPosition().y);
				settings.audio.soundVolume =
						(int) (soundVolumeSlider.getPosition().x - soundVolumeBar.getPosition().x + 12) / 4;
				menu[Buttons::SoundVolume].setString("Sound Volume : " + toString((int) settings.audio.soundVolume));
				setGlobalVolume();
				soundManager["button"].second.play();
			}
		}

		menu.handle();

		App.clear();
		App.draw(Background);
		App.draw(menu);
		App.draw(musicVolumeBar);
		App.draw(musicVolumeSlider);
		App.draw(soundVolumeBar);
		App.draw(soundVolumeSlider);
		App.display();
	}
	return -1;
}

