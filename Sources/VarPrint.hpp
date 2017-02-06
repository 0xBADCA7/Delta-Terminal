//
// Created by dylcl_000 on 08/12/2016.
//

#ifndef DELTA_TERMINAL_V2_VARPRINT_HPP
#define DELTA_TERMINAL_V2_VARPRINT_HPP

#include "TextureManager.hpp"

template<typename T>
string __(T t) {
	return to_string(t);
}

template<typename T>
string __(vector<T> t) {
	string s = "{";
	for (auto &i : t)                           //  Loop vector
		&i != &t.back() ?                       //  Unless this is the last item in loop
				s += __(i) + ","         //  print a comma after each
		                : s += __(i);    //  otherwise, just print item
	s += "}";
	return s;
}

template<typename T, typename S>
string __(pair<T, S> t) {
	return t.first + "->" + t.second;
}

template<>
string __(sf::VideoMode t) {
	return to_string(t.width) + "x" + to_string(t.height) + ":" + to_string(t.bitsPerPixel) + "bpp";
}

template<>
string __(sf::Color t) {
	return "(" +
	       to_string(t.r) + ", " +
	       to_string(t.g) + ", " +
	       to_string(t.b) + ")";
}

template<>
string __(string s) {
	return string("\"" + s + "\"");
}

template<>
string __(bool b) {
	return b ? "True" : "False";
}

template<>
string __(TextureManager T) {
	return __(T.getTextureNames());
}

template<typename T>
string __(sf::Vector2<T> t) {
	return "(" + to_string(t.x) + "," + to_string(t.y) + ")";
}

#define __(x) string(#x) + " = " + __(x)

#endif //DELTA_TERMINAL_V2_VARPRINT_HPP
