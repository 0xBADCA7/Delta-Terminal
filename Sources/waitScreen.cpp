#include "defines.hpp"
#include "dynamicMenu.hpp"
#include "menus.hpp"

int waitScreen() {
	Menu menu;

	sf::Texture splashTexture;
	splashTexture.loadFromFile("Graphics/Startup.png");

	bool stage2 = false,
			stage3 = false,
			toggle = true;

	sf::Sprite splash(splashTexture);
	splash.setColor(sf::Color(255, 255, 255, 0));

	sf::Clock timer;

	sf::Text Text("", Font, MENU_FONT_SIZE);

	auto stopWaiting = []() {
		throw 0;
	};

	menu.bindEvents(
			{
					make_pair(
							Event.KeyPressed,
							stopWaiting
					),
					make_pair(
							Event.MouseButtonPressed,
							stopWaiting
					),

			}
	);

	while (App.isOpen()) {
		while (App.pollEvent(Event)) {
			for (int i = sf::Event::EventType::Closed; i < sf::Event::EventType::Count; i++) {
				if (Event.type == (sf::Event::EventType) i && menu.eventManager.count((sf::Event::EventType) i) == 1) {
					try {
						menu.eventManager[Event.type]();
					}
					catch (int p) {
						App.clear();
						App.draw(Background);
						App.display();
						return 0;
					}
				}
			}
		}
		if (!stage2 && timer.getElapsedTime().asMilliseconds() > 1)
			timer.restart(), splash.setColor(sf::Color(255, 255, 255, splash.getColor().a + 4));

		if (!stage2 && splash.getColor().a > 240)
			stage2 = true;

		if (stage2 && !stage3) {
			Text.setString("Press any Key...");
			Text.setPosition((APP_WIDTH / 2) - Text.getGlobalBounds().width / 2,
			                 APP_HEIGHT - Text.getGlobalBounds().height - 80);
			stage3 = true;
		}

		if (stage3 && toggle && timer.getElapsedTime().asMilliseconds() > 1) {
			timer.restart();
			Text.setFillColor(sf::Color(255, 255, 255, (sf::Uint8) (Text.getFillColor().a - 4)));
			if (toggle && Text.getFillColor().a < 20)
				toggle = false;
		}

		if (stage3 && !toggle && timer.getElapsedTime().asMilliseconds() > 1) {
			timer.restart();
			Text.setFillColor(sf::Color(255, 255, 255, (sf::Uint8) (Text.getFillColor().a + 4)));
			if (!toggle && Text.getFillColor().a > 240)
				toggle = true;
		}

		menu.handle();
		App.clear();
		App.draw(Background);
		App.draw(splash);
		App.draw(Text);
		App.display();
		Framerate.restart();
	}
	return 0;
}
