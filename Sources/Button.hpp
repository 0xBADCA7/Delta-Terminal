#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "includes.hpp"

using namespace std;

extern sf::Font Font;

struct Button : public sf::Drawable {
private :
	sf::Text text;
	sf::Text subText;
	sf::RectangleShape button;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	function<void()> action;

	void operator()();

	void operator=(function<void()> pAction);

	Button &mimicStyles(Button &pButton);

	Button &setAction(function<void()> pAction);

	sf::FloatRect getGlobalBounds();

	Button &setFillColour(sf::Color colour);
	Button &setFontSize(unsigned fSize);
	Button &setOutlineColour(sf::Color colour);
	Button &setOutlineThickness(float px);
	Button &setString(string S);
	Button &setTextColour(sf::Color colour);
	Button &setPosition(sf::Vector2f pos);

	sf::Color getFillColour();
	unsigned getFontSize();
	sf::Color getOutlineColour();
	float getOutlineThickness();
	string getString();
	sf::Color getTextColour();
	sf::Vector2f getPosition();


	template<typename T>
	bool contains(T x, T y) {
		return button.getGlobalBounds().contains(x, y);
	}

	Button();
};


#endif // BUTTON_HPP
