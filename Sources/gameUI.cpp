#include "gameUI.hpp"
#include "defines.hpp"
#include "textureManager.hpp"
#include "audio.hpp"

sf::Color UIThemeColour;
sf::Color UIThemeSecondaryColour;

UITaskBar::UITaskBar() {
	UIThemeColour = sf::Color(20, 20, 255, 50);
	UIThemeSecondaryColour = sf::Color::Green;
	Bar.setSize(sf::Vector2f(APP_WIDTH, 100));
	Bar.setFillColor(UIThemeColour);
	Bar.setOutlineColor(sf::Color(35, 35, 35));
	Bar.setOutlineThickness(2);
	Bar.setPosition(0, 1080 - 100);
	for (int i = 0; i < MAXBUTTONS; i++) {
		buttons.push_back(sf::RectangleShape(sf::Vector2f(100, 100)));
		actions.push_back([&] {});
		auto &button = buttons.back();
		auto &action = actions.back();
		button.setOutlineThickness(1.5);
		button.setOutlineColor(sf::Color(35, 35, 35));
		button.setPosition(i * 106, APP_BOTTOM - 100);

		action = [&] {};

		switch (i) {
			case Quit:
				button.setTexture(&textureManager["UIButton-Quit"], false);
				break;

			case Programs:
				button.setTexture(&textureManager["UIButton-Programs"], false);
				break;

			case PC:
				button.setTexture(&textureManager["UIButton-PC"], false);
				break;

			case Media:
				button.setTexture(&textureManager["UIButton-Media"], false);
				action = [&] {
					nextSong();
				};
				break;

			default:
				button.setFillColor(UIThemeSecondaryColour);
				action = [&] { cout << "Empty" << endl; };
				break;
		}
	}
}

void UITaskBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(Bar, states);
	for (auto i : buttons) target.draw(i, states);
}

pair<sf::RectangleShape &, function<void()> &> UITaskBar::operator[](int index) {
	return pair<sf::RectangleShape &, function<void()> &>(buttons[index], actions[index]);
}
