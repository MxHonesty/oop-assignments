#include "UiError.h"

const char* UiError::what() const noexcept {
	return msg.c_str();
}
