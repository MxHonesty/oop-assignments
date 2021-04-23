#include "CosError.h"

const char* CosError::what() const noexcept {
	return msg.c_str();
}
