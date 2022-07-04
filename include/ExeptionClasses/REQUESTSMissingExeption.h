#pragma once
#include <exception>
#include <string>

class REQUESTSMissingExeption : public std::exception
{
public:
    REQUESTSMissingExeption() = default;
    REQUESTSMissingExeption(std::string msg) : message(msg){};
    const char* what() const noexcept override;
private:
    std::string message;
};
