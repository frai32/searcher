#include "JSONMissingExeption.h"

const char *JSONMissingExeption::what() const noexcept
{
    return message.c_str();
}
