#ifndef BACKGROUND_BUFFER_H
#define BACKGROUND_BUFFER_H

#include <string>
#include <vector>

struct Color {
	uint8_t r,g,b;
};

class BackgroundBuffer {
public:
	BackgroundBuffer(const uint16_t viewport_width, const uint16_t viewport_height);
	~BackgroundBuffer();

	void nextImageRaster(const std::string& file_path);
	Color** getImageBuffer(int& width, int& height);

private:

	uint16_t viewport_height, viewport_width;
	uint16_t image_height, image_width;
	Color** image_buffer;

};

#endif
