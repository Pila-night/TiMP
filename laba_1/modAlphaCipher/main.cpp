#include "modAlphaCipher.h"

#include <cctype>
#include <iostream>
#include <locale>
#include <string>

using namespace std;

bool isValid(const wstring& s)
{
    for(auto c : s) {
        if(!iswalpha(c) || !iswupper(c)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wstring key;
    wstring text;
    unsigned op;

    wcout << L"Введите ключ: ";
    wcin >> key;

    if(!isValid(key)) {
        wcerr << L"Ключ недействителен\n";
        return 1;
    }

    wcout << L"Ключ загружен\n";
    modAlphaCipher cipher(key);

    do {
        wcout << L"Шифр готов. Выберите операцию (0-выход, 1-зашифровать, 2-расшифровать): ";
        wcin >> op;

        if(op > 2) {
            cout << "Неправильная операция\n";
        } else if(op > 0) {
            cout << "Введите текст: ";
            wcin >> text;

            if(isValid(text)) {
                if(op == 1) {
                    wcout << L"Зашифрованный текст: " << endl;
                    wcout << cipher.encrypt(text) << endl;
                } else {
                    wcout << L"Расшифрованный текст: " << cipher.decrypt(text) << endl;
                }
            } else {
                wcout << "Operation aborted: неправильный текст\n";
            }
        }
    } while(op != 0);

    return 0;
}