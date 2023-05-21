/*
МОП ЭВМ ИКТИБ ЮФУ
Программирование и основы теории алгоритмов 2
Парахин А.О. КТбо1-7
Индивидуальное задание №4 Вариант 6
21.05.2023
*/

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Структура данных для хранения списка подстановок
typedef struct Table_Cell {
    string old_str = "-";  // Подстрока, которую нужно заменить.
    string new_str = "-";  // Подстрока, на которую нужно заменить.
    bool stopper = false;  // Является ли остоновочным действием 
                           // (true - является, false - не является)
} Table_Cell;

// Функция проверки вводимой строки на корректность.
// Функция проверяет введенное пользователем слово на 
// на соответствие ограничениям входных данных алгоритма,
// проходя по каждому символу входной строки и проверяя это.
// 
// Входные данные: 
//      Input - строка, которую нужно проверить на корректность.
// Выходные данные:
//      answer - true, если слово соответствует ограничениям, 
//               false, если не соответствует.
bool Check_Input(string Input);

// Функция инициализации списка подстановок.
// Функция открывает файл "Table.txt" и в цикле записывает в элементы 
// структур вектора Table список подстановок.
// 
// Входные данные: 
//      Table - vector для записи списка подстановок.
// Выходные данные: 
//      Нет, так как функция типа void.
void makeTable(vector <Table_Cell>& Table);

// Функция выбора и реализации подстановки для текущего слова и вывода
// результата шага.
// Функция получает на вход слово для обработки(word), 
// список подстановок(Table) и определитель завершения процесса(process). 
// Для каждого слова, начиная с первого, программа определяет применимую
// подстановку, выводит ее номер, выполняет ее и выводит ее результат в виде: (15) 12 -> *12
// В конце присваивает к process значение Table[i].stopper, 
// определяя, является ли эта замена последней в программе.
//
// Входные данные: 
//      word - строка для подстановки.
//      Table - список подстановок.
//      process - определитель завершения процесса.
// Выходные данные: 
//      Нет, так как функция типа void.
void makeAndPrintSubstitution(string& word, vector <Table_Cell>& Table, bool &process);

int main()
{
    setlocale(LC_ALL, "Russian");

    // Строка для хранения входного слова.
    string Input_string;
    // Хранение списка подстановок.
    vector <Table_Cell> Table;

    int flag = 1;
    do {
        cout << "Введите входное слово: ";
        cin >> Input_string;

        if (Check_Input(Input_string) == 1) {
            makeTable(Table);

            bool process = true;
            while (process) {
                makeAndPrintSubstitution(Input_string, Table, process);
            }
            cout << "Результат:" << Input_string << endl;
        }
        else {
            cout << "Ошибка. Строка не соответствует условию. Введите целое неотрицательное троичное число.";
        }

        cout << endl << "Хотите ввести входные данные заново или выйти из программы?" << endl
             << "(1 - Ввести входные данные заново, 0 - Выйти из программы): ";
        cin >> flag;
        cout << "-------------------------------------------------------------" << endl;
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

void makeAndPrintSubstitution(string& word, vector <Table_Cell>& Table, bool& process) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (word[0] != ' ') {
        word = " " + word;
    }

    int flag = 0;
    for (int i = 0; i < Table.size(); i++) {
        if (word.find(Table[i].old_str) != -1) {
            flag = 1;

            string old_str = Table[i].old_str;  // Какую подстроку заменить
            string new_str= Table[i].new_str;   // На какую строку заменить

            int start = word.find(old_str);     // Находим позицию подстроки

            // Output
            cout << "(" << i << ")";
            for (int i = 0; i < word.size(); i++) {
                if (i >= start && i < start + old_str.size()) {
                    SetConsoleTextAttribute(hConsole, 4);
                }
                cout << word[i];
                SetConsoleTextAttribute(hConsole, 7);
            }
            //

            word.replace(start, old_str.length(), new_str);   // Замена old_str на new_str

            if (word[0] != ' ') {
                word = " " + word;
            }

            cout << " ->" << word << endl;

            start = word.find(old_str, start + new_str.length());

            process = Table[i].stopper;
            break;
        }
    }
    if (flag == 0) {
        process = 0;
    }
    return;
}