#include "TableCipher.h"

#include <iostream>
#include <locale>
#include <string>
#include <vector>
using namespace std;
TableCipher::TableCipher(int key)
    : key(key)
{
}

/*std::wstring TableCipher::transformAndFilter(const std::wstring& text)
{
    // Преобразование регистра

    wstring preobrazovanie;
    for(wchar_t c : text) {
        preobrazovanie += towupper(c);
    }

    // Фильтрация

    wstring filtered;
    for(wchar_t c : preobrazovanie) {
        if((c >= L'А' && c <= L'Я') || c == L'Ё') {
            filtered += c;
        }
    }

    return filtered;
}*/

std::wstring TableCipher::encrypt(const std::wstring& text)
{
    // Вычисляем количество столбцов
    int rows;
    if(text.length() % key != 0) {
        rows = text.length() / key + 1;
    } else {
        rows = text.length() / key;
    }

    wchar_t table[rows][key];

    // Заполнение массива символами из строки text
    int index = 0;                     // индекс для перебора символов в строке text
    for(int i = 0; i < rows; i++) {    // проход по строкам таблицы
        for(int j = 0; j < key; j++) { // проход по столбцам
            if(index < text.length()) {
                table[i][j] = text[index];
                index++;
            } else {
                table[i][j] = L' '; 
            }
        }
    }

    std::wstring encrypted_text; // строка для хранения шифрованного текста

    // Изменяем порядок чтения на "сверху вниз, справа налево"
    for(int i = key - 1; i >= 0; i--) {
        for(int j = 0; j < rows; j++) {
            encrypted_text += table[j][i];
        }
    }

    return encrypted_text;
}

std::wstring TableCipher::decrypt(const std::wstring& encrypted_text)
{
    // Вычисляем высоту таблицы
    int rows = (encrypted_text.length() + key - 1) / key; // округление вверх

    // Создание двумерного массива символов размером rows на key
    wchar_t table[rows][key];

    int index = 0;
    for(int i = key - 1; i >= 0; i--) {
        for(int j = 0; j < rows; ++j) {
            if(index < encrypted_text.length()) {
                table[j][i] = encrypted_text[index];
                index++;
            } else {
                table[i][j] = L' ';
            }
        }
    }
    wstring decrypted_text;
    index = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < key; j++) {
            decrypted_text += table[i][j];
        }
    }
    return decrypted_text;
}
