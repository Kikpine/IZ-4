/*
МОП ЭВМ ИКТИБ ЮФУ
Программирование и основы теории алгоритмов 2
Парахин А.О. КТбо1-7
Индивидуальное задание №4 Вариант 6
20.05.2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef struct {
    string old_str;
    string new_str;
    bool stopper;
} Table_Cell;

// Функция проверки вводимой строки на корректность.
// Функция проверяет введенное пользователем слово на 
// на соответствие ограничениям входных данных алгоритма,
// проходя по каждому символу входной строки и проверяя это.
// 
// Входные данные: 
//      Input - строка, которую нужно проверить на корректность.
// Выходные данные:
//      answer - true, если слово соответствует ограничениям, false, если не соответствует.
bool Check_Input(string Input);

void makeTable(vector <Table_Cell>& Table);

void makeAndPrintSubstitution(string& word);

int main()
{
    setlocale(LC_ALL, "Russian");

    // Строка для хранения входного слова.
    string Input_string;
    // Структура данных для хранения списка подстановок.
    vector <Table_Cell> Table;

    int flag = 1;
    do {
        cout << "Введите входное слово: ";
        cin >> Input_string;
        cout << endl;
        if (Check_Input(Input_string) == 1) {
            makeTable(Table);

            makeAndPrintSubstitution(Input_string);
        }
        else {
            cout << "Ошибка. Строка не соответствует условию. Введите целое неотрицательное двоичное число.";
        }

        cout << endl << "Хотите ввести входные данные заново или выйти из программы? (1 - Ввести входные данные заново, 0 - Выйти из программы) : ";
        cin >> flag;
        cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
        if (flag != 1 && flag != 0) {
            cout << "Введена неизвестная операция. Доступные операции: 1 или 0." << endl;
            break;
        }
    } while (flag != 0);

    cout << "Вы вышли из программы." << endl;
    return 0;
}

bool Check_Input(string Input) {
    bool answer = true;
    for (auto it = Input.begin(); it != Input.end(); it++) {
        if (*it != '0' && *it != '1' && *it != '2') {
            answer = false;
        }
    }
    return answer;
}

void makeTable(vector <Table_Cell> &Table) {

    ifstream fin("Table.txt");

    int table_size;
    fin >> table_size;
    Table = vector <Table_Cell>(table_size+1);

    for (int i = 1; i <= table_size; i++) {
        getline(fin, Table[i].old_str, '\n');
        getline(fin, Table[i].old_str, '\t');
        getline(fin, Table[i].new_str, '\t');
        fin >> Table[i].stopper;
    }

    return;
}

void makeAndPrintSubstitution(string &word) {

    string old_str = "10";  // какую подстроку заменить
    string new_str = "@";  // на какую строку заменить
    int start = word.find(old_str);            // находим позицию подстроки
    if (start != -1) {
        word.replace(start, old_str.length(), new_str); // Замена old_str на new_str
        start = word.find(old_str, start + new_str.length());
    }
    cout << word << endl;

    return;
}