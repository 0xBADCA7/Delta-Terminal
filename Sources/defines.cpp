#include "includes.hpp"
#include "defines.hpp"
#include "game.hpp"

// void *_Unwind_Resume;
// void *__gxx_personality_v0;

mutex mtx;

sf::RenderWindow App;
sf::Event Event;
sf::View View;

sf::Clock Framerate;
sf::Font Font;

sf::Color ButtonFillColour(sf::Color::Transparent);
sf::Color ButtonHoverOutlineColour(sf::Color::Green);

sf::Sprite Background;

sf::Font CleanFont;
Settings settings;

GameEngine gameEngine;
