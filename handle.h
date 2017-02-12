#ifndef PANDEMIC_HANDLE_H
#define PANDEMIC_HANDLE_H

#include <string>

using handle = std::string;

auto inline operator ""_h(char const *s, long unsigned int count) -> handle {
	return std::string(s, count);
}

#endif //PANDEMIC_HANDLE_H
