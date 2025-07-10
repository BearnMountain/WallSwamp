#include "backgroundBuffer.h"
#include "stb_implementation.h"
#include <utility>

BackgroundBuffer::BackgroundBuffer(const uint16_t viewport_width, const uint16_t viewport_height) : 
	viewport_width(viewport_width), viewport_height(viewport_height), image_buffer(nullptr), image_height(0), image_width(0) {
	
}

BackgroundBuffer::~BackgroundBuffer() {
	// deletes the swap buffer
	for (uint8_t i = 0; i < image_height; i++) {
		delete[] image_buffer[i];
	}
}

void BackgroundBuffer::nextImageRaster(const std::string& file_path) {
	// cleanup of previous image
	for (uint16_t i = 0; i < image_height; i++) {
		delete[] image_buffer[i];
	}

	// downsampling image
	int width, height, channel;
	unsigned char* buffer = stbi_load(file_path.c_str(), &width, &height, &channel, 3);	

	// sampling
	float scale = std::min(
		(float)viewport_width / width,
		(float)viewport_height / height
	);
	int scaled_image_height = height * scale;
	int scaled_image_width = width * scale;
	
	int sample_box = 1 / scale;
	// creates new image_buffer and fills with average color of downsized areas
	image_buffer = new Color*[scaled_image_height];
	for (int y = 0; y < scaled_image_height; y++) {
		image_buffer[y] = new Color[scaled_image_width];
		for (int x = 0; x < scaled_image_width; x++) {
			Color clr;

			// parsing over the sample box
			for (int y_box = 0; y_box < sample_box; y_box++) {
				for (int x_box = 0; x_box < sample_box; x_box++) {
					clr.r += 0;
					clr.g += 0;
					clr.b += 0;
				}
			}

			image_buffer[y][x] = {
				static_cast<uint8_t>(clr.r / sample_box), 
				static_cast<uint8_t>(clr.g / sample_box), 
				static_cast<uint8_t>(clr.b / sample_box)
			};
		}
	}

	image_width = scaled_image_width;
	image_height = scaled_image_height;


Color** BackgroundBuffer::getImageBuffer(int& width, int& height) {
	width = image_width;
	height = image_height;
	return image_buffer;
}

