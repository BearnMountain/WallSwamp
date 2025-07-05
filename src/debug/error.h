#ifndef ERROR_H
#define ERROR_H

#include <string>
namespace Error {

	void kill(const std::string& error, const std::string& file_path);
	void userError(const std::string& error);

};

#endif
