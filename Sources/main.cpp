#include "includes.hpp"
#include "utilFunctions.hpp"
#include "resources.hpp"
#include "menus.hpp"
#include "audio.hpp"

struct Pulse {
	sf::CircleShape circle;
	sf::Clock timer;
	bool active;

	Pulse(sf::Vector2f coord) {
		active = true;
		circle.setRadius(5);
		circle.setPointCount(10);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(coord);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineThickness(0.5);
		circle.setOutlineColor(sf::Color::Green);
	}

	void handle() {
		if (timer.getElapsedTime().asSeconds() > (0.1 * Framerate.getElapsedTime().asSeconds())) {
			timer.restart();
			circle.scale(1.2, 1.2);
		}
		if (circle.getScale().x > 10) active = false;
	}
};

int main(int argc, char *argv[]) {
	srand(time(0));
	bool nosettings = false, nosplash = false;
	try {
		for (int i = 1; i < argc; i++) {
			if (string(argv[i]).find("nosettings") != string::npos)
				nosettings = true;
			if (string(argv[i]).find("nosplash") != string::npos)
				nosplash = true;
		}
		if (nosettings)
			settings.restoreAllDefaults();
		else settings.load();

		instanciateWindow();
		resourceInit();
		setGlobalVolume();
		if (settings.audio.musicEnabled && Songs.size() > 0)
			music.play();
	}
	catch (int e) {
		if (!App.isOpen()) {
			settings.graphics.VideoMode = sf::VideoMode(1920, 1080);
			if (sf::VideoMode::getFullscreenModes()[0] <= sf::VideoMode(1920, 1080))
				settings.graphics.VideoMode = sf::VideoMode::getFullscreenModes()[0];
			instanciateWindow();
		}
		errorScreen(e);
	}
	if (!nosplash) splashScreen();
	//
	//    sf::Clock timer;
	//    sf::Clock timer2;
	//    vector <sf::RectangleShape> dots;
	//    vector <sf::RectangleShape> lines;
	//    vector <Pulse> pulses;
	//    vector <sf::Vector2f> coords;
	//    fstream file;
	//
	//    file.open("Coords", fstream::in | fstream::binary);
	//    while (file.good()) {
	//        sf::Vector2f f;
	//        file.read((char *)&f, sizeof(sf::Vector2f));
	//        coords.push_back(f);
	//        }
	//    file.close();
	//
	//    for (vector<sf::Vector2f>::iterator ite = coords.begin(); ite != coords.end(); ) {
	//        if ((*ite).x < 5 && (*ite).y < 5) coords.erase(ite);
	//        else ite++;
	//        }
	//
	//    for (unsigned i = 0; i < coords.size(); i++) {
	//        for (unsigned j = 0; j < i; j++) if (coords[i].x > coords[j].x - 5 && coords[i].x < coords[j].x + 5 &&
	//                                                 coords[i].y > coords[j].y - 5 && coords[i].y < coords[j].y + 5) coords.erase(coords.begin() + i), i -= 2, cout << "Erased\n";
	//        }
	//
	//    for (auto i : coords) {
	//        dots.push_back(sf::RectangleShape (sf::Vector2f(4, 4)));
	//        dots.back().setSize(sf::Vector2f(4, 4));
	//        dots.back().setFillColor(sf::Color::White);
	//        dots.back().setOrigin(2, 2);
	//        dots.back().setPosition(i);
	//        }
	//    random_shuffle(dots.begin(), dots.end());
	//
	//    vector <sf::RectangleShape>::iterator vec = dots.begin();
	//    vector<Interactable> windows;
	//    windows.push_back(Interactable(200, 100, "See Here"));
	//    windows.back().setPosition(500, 100);
	//    windows.push_back(Interactable(100, 100, "Um, Here?"));
	//    windows.back().setPosition(400, 150);
	//    windows.push_back(Interactable(200, 100, "See There"));
	//    windows.back().setPosition(600, 200);
	//
	//    if (Event.type == Event.MouseButtonPressed) {
	//                pulses.push_back(Pulse(sf::Vector2f(Event.mouseButton.x, Event.mouseButton.y)));
	//                }
	//
	//    if (settings.graphics.fullscreenEnabled) App.create(sf::VideoMode(1920, 1080), GAMENAME, sf::Style::Fullscreen);
	//    else App.create(sf::VideoMode(1920, 1080), GAMENAME, sf::Style::Close);

	waitScreen();
	mainMenu();

	//    while (App.isOpen()) {
	//        while (App.pollEvent (Event) ) {
	//            for (int i = sf::Event::EventType::Closed; i < sf::Event::EventType::Count; i++) {
	//                if (Event.type == (sf::Event::EventType) i && eventBinds.count ( (sf::Event::EventType) i) == 1) {
	//                    try {eventBinds[Event.type]();}
	//                    catch (int p) {return 0;}
	//                    }
	//                }
	//            InteractableEvent(Event, windows);
	//            }
	//
	//        App.clear();
	//        App.draw(Background);
	//        if (lines.size() > 0) for (auto i : lines) App.draw(i);
	//        if (dots.size() >  0) for (auto i : dots) App.draw(i);
	//        if (pulses.size() > 0) for (vector<Pulse>::iterator i = pulses.begin(); i != pulses.end();) {
	//                if (i->active) i->handle(), App.draw(i->circle), i++;
	//                else pulses.erase(i);
	//                }
	//        InteractableDrawHandle(App, windows);
	//        App.display();
	//        Framerate.restart();
	//        }
	//        if(timer2.getElapsedTime().asSeconds() > 2 && lines.size() > 1) {
	//            vector <sf::RectangleShape>::iterator ite = lines.begin();
	//            lines.erase(ite);
	//            vec--;
	//            timer2.restart();
	//            }
	//
	//        if(timer.getElapsedTime().asSeconds() > 0.5 && dots.size() > 1 && vec != dots.end()) {
	//            float xDiff, yDiff;
	//
	//            vector <sf::RectangleShape>::iterator ite = vec - 1;
	//            xDiff = vec->getPosition().x - ite->getPosition().x;
	//            yDiff = vec->getPosition().y - ite->getPosition().y;
	//
	//            float difference = sqrt(pow(xDiff, 2) + pow(yDiff, 2));
	//
	//
	//            lines.push_back(sf::RectangleShape (sf::Vector2f(difference, 2)));
	//            lines.back().setPosition(vec->getPosition());
	//            lines.back().setFillColor(sf::Color::Blue);
	//            lines.back().setSize(sf::Vector2f(difference, 2));
	//            lines.back().setRotation(atan2(yDiff, xDiff) * (180 / 3.1415) - 180);
	//            vec++;
	//            timer.restart();
	//            }
	//    file.open("Coords", fstream::out | fstream::binary);
	//    for (auto i : coords) file.write((char *)&i, sizeof(sf::Vector2f));
	//    file.close();
	exit(0);
}
