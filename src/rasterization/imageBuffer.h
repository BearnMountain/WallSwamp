#ifndef IMAGE_BUFFER_H
#define IMAGE_BUFFER_H

#include <string>


class ImageBuffer {
public:
	ImageBuffer();
	~ImageBuffer();

	void rasterImage(const std::string& file_path);
	unsigned char* getImageBuffer(int& width, int& height, int& buffer_length);

private:
	struct vec3 {
		uint8_t r,g,b;
	};
	struct vec2 {
		int x, y;
	};

	int width, height, channels;
	int buffer_length;
	unsigned char* data_buffer;


};

#endif
