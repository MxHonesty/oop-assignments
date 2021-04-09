#include "FileError.h"

const char* FileError::what() const noexcept {
	return msg.c_str();
}
