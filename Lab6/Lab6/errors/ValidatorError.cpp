#include "ValidatorError.h"

const char* ValidatorError::what() const noexcept {
	return msg.c_str();
}
