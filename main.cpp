#include <iostream>
#include "application.h"

auto main() -> int {
	application application(std::cin, std::cout);
	application.run();
	return 0;
}
