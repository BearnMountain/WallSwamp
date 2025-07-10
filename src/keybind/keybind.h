#ifndef KEYBIND_H
#define KEYBIND_H

#include <functional>
#include <unordered_map>
#include <vector>

class Keybind {
public:
	Keybind();
	~Keybind();

	void processKeypress();
	void bind(const char key, const std::function<void()> client); // insert like {'a', '\0'} or {\x1b}


private:
	std::unordered_map<char, std::vector<std::function<void()>>> key_bindings;
	char readKey();
};

#endif
