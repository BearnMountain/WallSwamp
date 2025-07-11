#include "keybind.h"
#include "../../res/config.h"

#include <functional>
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

Keybind::Keybind() {

}

Keybind::~Keybind() {

}

void Keybind::bind(const char key, const std::function<void()> client) {
	key_bindings[key].push_back(client);
}

char Keybind::readKey() {
	int input;
	char c;

	while ((input == read(STDIN_FILENO, &c, 1)) != 1) {
		if (input == -1 && errno != EAGAIN) std::exit(1);
	}

	// reads special sequences
	if (c == '\x1b') {
		char sequence[3];
		
		if (read(STDIN_FILENO, &sequence[0], 1) != 1 && read(STDIN_FILENO, &sequence[1], 1) != 1) return '\x1b';

		// arrow keys
		if (sequence[0] == '[') {
			switch (sequence[1]) {
				case 'A': return MOVE_UP;
				case 'B': return MOVE_DOWN;
				case 'C': return MOVE_RIGHT;
				case 'D': return MOVE_LEFT;
				default: break;
			}
		}

		return '\x1b';
	}

	return c;
}

char Keybind::processKeypress() {
	char c = readKey();

	// checks bindings
	if (key_bindings.find(c) != key_bindings.end()) {
		for (std::function<void()>& callback : key_bindings[c]) {
			callback();
		}
	}

	return c;
}
