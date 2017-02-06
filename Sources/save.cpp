#include "save.hpp"
#include "settings.hpp"

void saveAndQuit() {
	settings.save();
	exit(0);
}
