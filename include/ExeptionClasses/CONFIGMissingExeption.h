#pragma once
#include <exception>
#include <string>

//Класс для обработки исключений связаных с файлами JSON
class CONFIGMissingExeption : public std::exception{
public:
    CONFIGMissingExeption() = default;
    CONFIGMissingExeption(std::string msg) : message(msg){};
    const char* what() const noexcept override;

private:
std::string message;//собщение ошибки
};
