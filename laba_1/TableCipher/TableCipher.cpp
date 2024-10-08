#include "TableCipher.h"

#include <iostream>
#include <locale>
#include <string>
using namespace std;

TableCipher::TableCipher(int key)
    : key(key)
{
}

std::wstring TableCipher::encrypt(const std::wstring& text)
{
    //вычисляем количество столбцов
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

    // порядок чтения на "сверху вниз, справа налево"
    for(int i = key - 1; i >= 0; i--) {
        for(int j = 0; j < rows; j++) {
            encrypted_text += table[j][i];
        }
    }

    return encrypted_text;
}

std::wstring TableCipher::decrypt(const std::wstring& encrypted_text)
{
    //вычисляем количество столбцов
    int rows;
    if(encrypted_text.length() % key != 0) {
        rows = encrypted_text.length() / key + 1;
    } else {
        rows = encrypted_text.length() / key;
    }

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