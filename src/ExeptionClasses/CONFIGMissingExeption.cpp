#include "CONFIGMissingExeption.h"

const char *CONFIGMissingExeption::what() const noexcept
{
    return message.c_str();
}
