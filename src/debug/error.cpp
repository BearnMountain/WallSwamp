#include "error.h"
#include <iostream>

void Error::kill(const std::string& error, const std::string& file_path) {
	std::cout << "[KILL] " << file_path << " : " << error << std::endl;
	exit(1);
}
