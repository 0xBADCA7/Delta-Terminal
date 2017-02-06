#include "includes.hpp"
#include "defines.hpp"

template<typename T>
string toString(T t);

template<typename T>
string toString(T *t);

string toLowerCase(string);
string toUpperCase(string);
string toTitleCase(string);
string splitCamelCase(string);

bool fileExists(string filename);

double mod(double x);

void lineWrapText(sf::Text &text, int MaxXPos);
