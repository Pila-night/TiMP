#pragma once
#include <map>
#include <string>
#include <vector>
class modAlphaCipher
{
private:
std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    std::map<char, int> alphaNum;
    std::vector<int> key;
    std::vector<int> convert(const std::wstring& s); 
    std::wstring convert(const std::vector<int>& v); 
public:
    modAlphaCipher() = delete;
    modAlphaCipher(const std::wstring& skey);
    std::wstring encrypt(const std::wstring& open_text);   
    std::wstring decrypt(const std::wstring& cipher_text); 
};