#include "RepoError.h"

const char* RepoError::what() const noexcept {
	return msg.c_str();
}
