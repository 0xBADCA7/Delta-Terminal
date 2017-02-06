#ifndef MENUS_HPP
#define MENUS_HPP

int mainMenu();

int creditsMenu();

int errorScreen(int errorCode);

int graphicsOptionsMenu();

int optionsMenu();

int pauseMenu();

int splashScreen();

int waitScreen();

#ifdef DEVMODE
int devMenu();
#endif // DEVMODE

#endif // MENUS_HPP

