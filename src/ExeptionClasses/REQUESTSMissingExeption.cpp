#include "REQUESTSMissingExeption.h"


const char *REQUESTSMissingExeption::what() const noexcept {
    return message.c_str();
}
