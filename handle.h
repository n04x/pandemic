#ifndef PANDEMIC_HANDLE_H
#define PANDEMIC_HANDLE_H

#include <string>

// handle represents an opaque identifier for a game object.
struct handle {
	inline handle() : name{} {
	}

	inline handle(std::string name) : name{name} {
	}

	friend auto operator<(handle const &lhs, handle const &rhs) -> bool;

	friend auto operator==(handle const &lhs, handle const &rhs) -> bool;

	friend auto operator<<(std::ostream &os, const handle &h) -> std::ostream &;

private:
	std::string name;
};

// _h returns a handle for the given string
inline auto operator ""_h(char const *s, std::size_t count) -> handle {
	return handle{std::string{s, count}};
}

// == returns true if lhs and rhs represent the same game object
inline auto operator==(handle const &lhs, handle const &rhs) -> bool {
	return lhs.name == rhs.name;
}

// == returns true if lhs and rhs do not represent the same game object
inline auto operator!=(handle const &lhs, handle const &rhs) -> bool {
	return !(lhs == rhs);
}

// < returns true if lhs is less than rhs
inline auto operator<(handle const &lhs, handle const &rhs) -> bool {
	return lhs.name < rhs.name;
}

// << writes the handle to the given stream
inline auto operator<<(std::ostream &os, const handle &h) -> std::ostream & {
	os << h.name;
	return os;
}

#endif //PANDEMIC_HANDLE_H
