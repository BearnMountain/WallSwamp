#include <cstdio>
#include <sys/ttycom.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#include "terminal.h"
#include "../debug/error.h"

Terminal::Terminal() {
	struct winsize window;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window) == -1 || window.ws_col == 0) {
		if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12) Error::kill("window size failed to initialize", "src/tui/terminal.cpp");

		char buffer[32];
		unsigned int i = 0;

		if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) Error::kill("window failed to initialize", "src/tui/terminal.cpp");

		while (i < sizeof(buffer) - 1) {
			if (read(STDIN_FILENO, &buffer[i], 1) != 1) break;
			if (buffer[i] == 'R') break;

			i++;
		}
		buffer[i] = '\0';

		// reads buffered cursor pos
		if (buffer[0] != '\x1b' || buffer[1] != '[') Error::kill("window failed to initialize", "src/tui/terminal.cpp");
		int rows, cols;
		if (sscanf(&buffer[2], "%d;%d", &rows, &cols) != 2) Error::kill("window failed to initialize", "src/tui/terminal.cpp");

	} else {
		screen_rows = window.ws_row;
		screen_cols = window.ws_col;
	}

	screen_rows--; // last row is for the status buffer
	cursor_x = 0;
	cursor_y = 0;
	
}

Terminal::~Terminal() {

}

void Terminal::enableRawMode() {

}

void Terminal::disableRawMode() {
	
}

void Terminal::setCursor(const uint16_t x, const uint16_t y) {
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "\x1b[%x;%dH", y, x);
	write(STDOUT_FILENO, buffer, strlen(buffer));
	
	cursor_x = x;
	cursor_y = y;
}
