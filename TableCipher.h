#pragma once
#include <string>

class TableCipher
{
private:
    int key;
public:
    TableCipher() = delete; // запрет конструктора по умолчанию
    TableCipher(int key);   // конструктор класса
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& encrypted_text);
};
