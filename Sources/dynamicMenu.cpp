#include "dynamicMenu.hpp"
#include "defines.hpp"
#include "resources.hpp"
#include "audio.hpp"
#include "utilFunctions.hpp"


Menu::Menu() {
	// NOTE (Dylan #3 2015-08-23 ):  Event Bind Defaults Here
	eventManager = {
			make_pair(
					sf::Event::Closed,
					[&]() {
						App.close();
					}
			),
			make_pair(
					sf::Event::MouseMoved,
					[&] {
						hover();
					}
			),
			make_pair(
					sf::Event::KeyPressed,
					[]() {
						if (Event.key.code == sf::Keyboard::Key::Escape)
							throw (0);
					}
			)
	};
	eventManager[sf::Event::MouseButtonPressed] = [&]() {
		for (auto i : buttonManager) {
			if (subMenuEntered) {
				subMenuEntered = false;
				break;
			}
			if ((*i).contains(App.mapPixelToCoords(sf::Vector2i(Event.mouseButton.x, Event.mouseButton.y)).x,
			                  App.mapPixelToCoords(sf::Vector2i(Event.mouseButton.x, Event.mouseButton.y)).y)) {
				if (soundManager.count("button") > 0 && settings.audio.soundEnabled)
					soundManager["button"].second.play();
				(*i).action();
			}
		}
	};

	Title.setPosition(sf::Vector2f(50, 20));
	Title.setFont(Font);
	Title.setCharacterSize(MENU_FONT_SIZE * 2);
	Title.setStyle(sf::Text::Style::Bold);
	Title.setString("Menu");
	Title.setFillColor(sf::Color::White);

	TitleUnderline.setString(". . . . . . . . . . . . . . . . ");
	TitleUnderline.setFont(Font);
	TitleUnderline.setCharacterSize(MENU_FONT_SIZE);
	TitleUnderline.setStyle(sf::Text::Style::Bold);
	TitleUnderline.setFillColor(sf::Color::White);
	TitleUnderline.setPosition(sf::Vector2f(50, 20 + Font.getLineSpacing(Title.getCharacterSize() + 5)));

	FramerateDisplay = sf::Text("60", Font, MENU_FONT_SIZE * 1.2);
	FramerateDisplay.setPosition(APP_WIDTH - FramerateDisplay.getGlobalBounds().width - 10, 10);
	subMenuEntered = false;
}

void Menu::setTitle(string s) {
	Title.setString(s);
}

Button &Menu::newButton(string s, float x, float y) {
	buttonManager.push_back(new Button);
	buttonManager.back()->setString(s).setPosition(sf::Vector2f(x, y));
	return *buttonManager.back();
}

Button &Menu::newButton(string s) {
	buttonManager.push_back(new Button);
	buttonManager.back()->setString(s);
	if (buttonManager.size() == 1) buttonManager.back()->setPosition(sf::Vector2f(50, 300));
	else
		buttonManager.back()->setPosition(
				sf::Vector2f(50, buttonManager[buttonManager.size() - 2]->getPosition().y + 100));
	return *buttonManager.back();
}

void Menu::bindEvent(sf::Event::EventType eType, function<void()> pAction) {
	eventManager[eType] = pAction;
}

void Menu::bindEvents(map<sf::Event::EventType, function<void()>> pList) {
	for (auto i : pList)
		eventManager[i.first] = i.second;
}

void Menu::hover() {
	for (auto i : buttonManager) {
		if ((*i).contains(mapPixelToCoords(sf::Mouse::getPosition(App)).x,
		                  mapPixelToCoords(sf::Mouse::getPosition(App)).y)) {
			(*i).setOutlineThickness(2);
		} else (*i).setOutlineThickness(0);
	}
}

string Menu::getTitle() {
	return Title.getString();
}

Button &Menu::operator[](int i) {
	return *buttonManager[i];
}

void Menu::handle() {
	if (FPSDisplayTimeout.getElapsedTime().asSeconds() > 0.5) {
		FramerateDisplay.setString(toString((int) (1.0 / Framerate.getElapsedTime().asSeconds())));
		FramerateDisplay.setPosition(APP_WIDTH - FramerateDisplay.getGlobalBounds().width - 10, 10);
		FPSDisplayTimeout.restart();
	}
	Framerate.restart();
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	if (!suppressTitle) {
		target.draw(Title, states);
		target.draw(TitleUnderline, states);
	}
	if (settings.graphics.displayFramerate)
		target.draw(FramerateDisplay, states);
	for (auto i : buttonManager)
		target.draw(*i, states);
}

