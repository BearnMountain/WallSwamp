#ifndef BACKGROUND_BUFFER_H
#define BACKGROUND_BUFFER_H 

#include <cstdlib>
#include <string>

struct Color {
	uint8_t r,g,b;
};

class BackgroundBuffer {
private:

	BackgroundBuffer(const uint16_t viewport_width, const uint16_t viewport_height);
	~BackgroundBuffer();

	void nextImageRaster(const std::string& file_path);
	Color** getImageBuffer(int& width, int& height);

public:
	uint16_t viewport_width, viewport_height;
	uint16_t image_width, image_height;
	Color** image_buffer;
};

#endif
