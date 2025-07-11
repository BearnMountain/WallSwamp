#include <iostream>
#include <string>

#include "tui/render.h"
#include "tui/terminal.h"
#include "keybind/keybind.h"

int main(void) {
	
	std::string file = "~/Desktop/Images/";
	
	Terminal terminal;
	Render render;
	Keybind key_bind;

	std::string search_query = "";
	bool in_search_mode = false;
	bool running = true;

	terminal.enableRawMode();

	// setting up keybinds
	key_bind.bind(CTRL('q'), [&running] { running = false; });
	key_bind.bind(CTRL('c'), [&running] { running = false; });
	key_bind.bind('/', [&search_query, &in_search_mode] { if (!in_search_mode) {search_query.clear(); in_search_mode = true;} });

	while (running) {
		 char c = key_bind.processKeypress();

		if () {

		}
	}

	terminal.disableRawMode();

	return 0;
}

