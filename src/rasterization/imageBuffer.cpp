#include "imageBuffer.h"
#include "stb_implementation.h"

ImageBuffer::ImageBuffer() {

}

ImageBuffer::~ImageBuffer() {

}

void rasterImage(const std::string& file_path) {
	unsigned char* buffer = stbi_load
}

unsigned char* getImageBuffer(int& width, int& height, int& buffer_length) {
	width = width;
	height = height;
	buffer_length = buffer_length;
	return data_buffer;
}
