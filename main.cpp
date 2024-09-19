#include <TableCipher.h>
#include <iostream>
#include <locale>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int key;
    wstring text;
    unsigned op;

    wcout << L"Введите ключ: ";
    wcin >> key;
    wcin.ignore(); // Игнорируем символ новой строки после ввода ключа

    wcout << L"Ключ загружен\n";
    TableCipher cipher(key);

    do {
        wcout << L"Шифр готов. Выберите операцию (0-выход, 1-зашифровать, 2-расшифровать, 3-сменить ключ): ";
        wcin >> op;
        wcin.ignore(); // Игнорируем символ новой строки после ввода операции

        if (op > 3) {
            wcout << L"Неправильная операция\n";
        } else if (op == 3) {
            // Смена ключа
            wcout << L"Введите новый ключ: ";
            wcin >> key;
            wcin.ignore(); // Игнорируем символ новой строки после ввода нового ключа
            cipher = TableCipher(key); // Обновляем шифратор с новым ключом
            wcout << L"Ключ успешно изменён\n";
        } else if (op > 0) {
            wcout << L"Введите текст: ";
            getline(wcin, text); // Используем getline для считывания всей строки

            if (op == 1) {
                wcout << L"Зашифрованный текст: " << endl;
                wcout << cipher.encrypt(text) << endl;
            } else {
                wcout << L"Расшифрованный текст: " << cipher.decrypt(text) << endl;
            }
        } else {
            wcout << L"Операция отменена: неправильный текст\n";
        }

    } while (op != 0);

    return 0;
}
