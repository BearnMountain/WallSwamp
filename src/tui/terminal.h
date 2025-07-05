#ifndef TERMINAL_H
#define TERMINAL_H

#include <cstdint>
#include <termios.h>


class Terminal {
public:

	Terminal();
	~Terminal();

	void init();
	void disableRawMode();
	void enableRawMode();
	
	// GETTERS
	inline const uint16_t getCursorX() { return cursor_x; }	
	inline const uint16_t getCursorY() { return cursor_y; }	
	inline const uint16_t getTerminalHeight() { return screen_rows; }
	inline const uint16_t getTerminalWidth()  { return screen_rows; }

	// SETTERS
	void setCursor(const uint16_t x, const uint16_t y);

private:
	uint16_t cursor_x, cursor_y;
	uint16_t screen_rows, screen_cols;
	struct termios original_terminal;
};

#endif
