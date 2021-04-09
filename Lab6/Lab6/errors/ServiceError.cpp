#include "ServiceError.h"
#include <memory>

const char* ServiceError::what() const noexcept {
    return msg.c_str();    
}
