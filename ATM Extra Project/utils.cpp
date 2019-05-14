#include <string>
#include <cstdint>
#include "utils.hpp"

uint64_t utils::hashpw(std::string* input) {
	return input->length() % UINT64_MAX;
}
