#include <unistd.h>

#include "render.h"

Render::Render(const uint16_t screen_width, const uint16_t screen_height, const std::vector<std::string>& file_path) : file_path(std::move(file_path)) {

	screen_buffer.screen_width = screen_width;
	screen_buffer.screen_height = screen_height;
	screen_buffer.buffer = new char*[screen_height];
	for (uint16_t i = 0; i < screen_buffer.screen_height; i++) {
		screen_buffer.buffer[i] = new char[screen_width];
		for (uint16_t j = 0; j < screen_buffer.screen_width; j++) {
			screen_buffer.buffer[i][j] = ' ';
		}
	}

	// creating update buffer
	screen_buffer.redraw = false;
	screen_buffer.update_line = new bool[screen_height];
	std::memset(screen_buffer.update_line, 1, screen_height * sizeof(bool));
}

Render::~Render() {

}

void Render::refresh() {
	if (!screen_buffer.redraw) return;

	char cursor_buffer[16];


	for (uint16_t i = 0; i < screen_buffer.screen_height; i++) {
		if (screen_buffer.update_line[i]) {
			// moves cursor to current line
			snprintf(cursor_buffer, sizeof(cursor_buffer), "\x1b[%d;1H", i + 1);
			write(STDOUT_FILENO, cursor_buffer, strlen(cursor_buffer));	

			// clears line
			write(STDOUT_FILENO, "\x1b[K", 3);
			
			// write line
			write(STDOUT_FILENO, screen_buffer.buffer[i], screen_buffer.screen_width);

			// resets line opt
			screen_buffer.update_line[i] = false;
			screen_buffer.redraw = false;
		}
	}
}
/*
void statusbar() {
	char cursor_buffer[16];
	snprintf(cursor_buffer, sizeof(cursor_buffer), "\x1b[%d;1H", screen_buffer.height + 1);
	write(STDOUT_FILENO, cursor_buffer, strlen(cursor_buffer));

	// clears line
	write(STDOUT_FILENO, "\x1b[K", 3);
	
	// set background
	write(STDOUT_FILENO, STATUS_BAR_BACKGROUND_COLOR, strlen(STATUS_BAR_BACKGROUND_COLOR));

	// print status_bar
	write(STDOUT_FILENO, status_bar.buffer, status_bar.buffer_length);

	// reset
	write(STDOUT_FILENO, "\x1b[0m", 4); // resets color
	snprintf(cursor_buffer, sizeof(cursor_buffer), "\x1b[%d;%dH", term.cursor_y, term.cursor_x);
	write(STDOUT_FILENO, cursor_buffer, strlen(cursor_buffer));
	fsync(STDOUT_FILENO);
}
*/
