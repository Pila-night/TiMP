#include "TableCipher.h"

#include <iostream>
#include <locale>
#include <string>
using namespace std;
TableCipher::TableCipher(int key)
    : key(key)
{
}

std::wstring TableCipher::transformAndFilter(const std::wstring& text)
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
}

std::wstring TableCipher::encrypt(const std::wstring& text)
{
    std::wstring filtered = transformAndFilter(text);

    // Вычисляем количество столбцов
    int rows;
    if(filtered.length() % key != 0) {
        rows = filtered.length() / key + 1;
    } else {
        rows = filtered.length() / key;
    }

    wchar_t table[rows][key];

    // Заполнение массива символами из строки filtered
    int index = 0;                     // индекс для перебора символов в строке filtered
    for(int i = 0; i < rows; i++) {    // проход по строкам таблицы
        for(int j = 0; j < key; j++) { // проход по столбцам
            if(index < filtered.length()) {
                table[i][j] = filtered[index];
                index++;
            } else {
                table[i][j] = L'\0'; // используем нулевой символ для обозначения пустой ячейки
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
    // Вычисляем количество строк
    int rows;
    if(encrypted_text.length() % key != 0) {
        rows = encrypted_text.length() / key + 1;
    } else {
        rows = encrypted_text.length() / key;
    }

    wchar_t table[rows][key];

    int index = 0;

    // Заполнение массива для расшифровки
    for(int i = 0; i < key; i++) {
        for(int j = 0; j < rows; j++) {
            if(index < encrypted_text.length()) {
                table[j][i] = encrypted_text[index];
                index++;
            } else {
                table[j][i] = L'\0'; // используем нулевой символ для обозначения пустой ячейки
            }
        }
    }

    std::wstring decrypted_text;

    // Чтение из таблицы в правильном порядке для расшифровки
    for(int i = 0; i < rows; i++) {
        for(int j = key - 1; j >= 0; j--) { // Изменяем порядок чтения на "сверху вниз, справа налево"
            if(table[i][j] != L'\0') {
                decrypted_text += table[i][j];
            }
        }
    }

    return decrypted_text;
}
