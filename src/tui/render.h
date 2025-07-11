#ifndef RENDER_H
#define RENDER_H

#include <cstdint>
#include <vector>
#include <string>

struct ScreenBuffer {
	uint16_t screen_width, screen_height;
	char** buffer;
	bool* update_line;
	bool redraw;

	struct SearchBuffer {
		uint16_t x, y;
		uint16_t screen_width, screen_height;
		std::string search_query;
	};

	struct SelectionBuffer {
		uint16_t x, y;
		uint16_t screen_width, screen_height;
	};

	struct BackgroundBuffer {
		uint16_t x, y;
		uint16_t screen_width, screen_height;
	};

	struct StatusBarBuffer {
		char* line_buffer;
	};
};

class Render {
public:
	Render(const uint16_t screen_width, const uint16_t screen_height, const std::vector<std::string>& file_path);
	~Render();

	void refresh();

	void updateStatusBar(); // status_bar is the bottom line of screen_buffer
	void updateSearch(const std::string& query);
	void nextBackground();
	void previousBackground();

private:
	ScreenBuffer screen_buffer;

	std::vector<std::string> file_path;
	uint16_t file_position; 
};

#endif
