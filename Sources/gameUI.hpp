#ifndef GAME_UI
#define GAME_UI

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

using namespace std;

extern sf::Color UIThemeColour;
extern sf::Color UIThemeSecondaryColour;

struct UITaskBar : public sf::Drawable {
	sf::RectangleShape Bar;
	vector<sf::RectangleShape> buttons;
	vector<function<void() >> actions;

	enum {
		Quit = 0,
		Programs,
		PC,
		Media,
		MAXBUTTONS
	};

	UITaskBar();

	pair<sf::RectangleShape &, function<void()> &> operator[](int index);

private :
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

struct UITaskBarMenu : public sf::Drawable {
	sf::RectangleShape Container;
	vector<sf::RectangleShape> buttons;
	vector<function<void() >> actions;

	UITaskBarMenu();

	UITaskBarMenu(float width, float height);

	void newButton();

private :
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void updateLayout();
};


#endif // GAME_UI
