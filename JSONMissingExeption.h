#pragma once
#include <exception>
#include <string>

//Класс для обработки исключений связаных с файлами JSON
class JSONMissingExeption : public std::exception{
public:
    JSONMissingExeption() = default;
    JSONMissingExeption(std::string msg) : message(msg){};
    const char* what() const noexcept override;

private:
std::string message;//собщение ошибки
};
