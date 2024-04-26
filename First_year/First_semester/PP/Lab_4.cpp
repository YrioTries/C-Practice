#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <string>
using namespace std;

int main()
{
    double FinalTime_ofString = 0, FinalTime_ofChar = 0, StartTime_ofChar, StartTime_ofString, EndTime_ofChar, EndTime_ofString;
    setlocale(LC_ALL, "Russian");


    for (int i = 0; i < 10; i++)
    {


        vector <char> vec; // вектор для хранения значений из файла

        ifstream fin; // создание объекта класса ifstream (файловый ввод)

        fin.open("input.txt"); // связывание объекта с файлом

        if (!fin.is_open()) // проверка на корректное открытие файла
        {
            cout << "Ошибка! Файл не был открыт" << endl;
        }

        char symbol; // переменная типа char

        char prov = ' '; // символ, частоту встречаемости которого надо вычислить
        int j; // переменная которая запоминает позицию искомого символа

        while (fin.get(symbol)) // Пока в файле есть символы, файл посимвольно добавляется в вектор
        {

            vec.push_back(symbol);
        }

        j = vec.size() - 1;
        prov = vec[j]; // Находим переменную
        vec.clear();

        fin.close();

        StartTime_ofChar = clock();

        fin.open("input.txt"); // Связывание объекта с файлом

        while (fin.get(symbol)) // Пока в файле есть символы, файл посимвольно добавляется в вектор
        {
            if ((symbol != ' ') && (symbol != '.') && (symbol != '/') && (symbol != ',') && (symbol != ';') && (symbol != '`')) {

                if (islower(prov)) // Используем макрос для коректного заполнения вектора
                {
                    symbol = tolower(symbol);

                }
                else
                {
                    symbol = toupper(symbol);
                }
            }

            vec.push_back(symbol); // Заполнение вектора
        }

        fin.close();



        int k = 0; // Переменная счётчика

        for (int i = 0; i < (j - 1); i++) // Поиск и подсчёт количества повторений нужного символа
        {
            if (vec[i] == prov) // Сравниваем 
            {
                k += 1;
            }
        }


        ofstream fout; // Создание объекта класса ofstream (файловый вывод)

        fout.open("OutputChar.txt"); // Связывание объекта с файло
        fout << " \n(Char) Number of occurences of a number in the data array: " << k; // Передача значения в файл 
        fout.close();

        EndTime_ofChar = clock();

        StartTime_ofString = clock();

        string path = "input.txt"; // Связываем с нужным текстовым файлом
        int f = 0;
        string msg;
        fstream fs;
        fs.open(path, fstream::in | fstream::out); // Перегрузка fs для ввода и вывода

        if (!fs.is_open())
        {
            cout << " Error of openning file!" << endl;
        }

        getline(fs, msg); // Записываем строку в msg


        for (int i = 0; i < msg.size(); i++)
        {
            if (tolower(msg[i]) == tolower(prov)) {

                f += 1; // Подсчёт количества вхождений
            }

            //if ((msg[i] == prov) || (((64 < msg[i] < 91) && (msg[i] + 32 == prov)) || ((96 < msg[i] < 123) && (msg[i] - 32 == prov)))) // Используем таблицу ASCII
            //{
            //    f += 1; // Подсчёт количества вхождений
            //}
        }

        fs.close();

        string path2 = "OutputString.txt"; // Связываем с нужным текстовым файлом
        fstream fs2;
        fs2.open(path2, fstream::in | fstream::out); // Перегрузка fs для ввода и вывода

        fs2 << " \n(String) Number of occurences of a number in the data array: " << f << endl; // Выводим информацию в файл

        fs2.close();

        EndTime_ofString = clock();

        FinalTime_ofString += (double)(EndTime_ofString - StartTime_ofString) / CLOCKS_PER_SEC; // Подсчёт времени работы String и Char
        FinalTime_ofChar += (double)(EndTime_ofChar - StartTime_ofChar) / CLOCKS_PER_SEC;

    }
    cout << " Char time is: " << FinalTime_ofChar << " seconds" << endl; // Вывод времени на консоль
    cout << " String time is: " << FinalTime_ofString << " seconds" << endl;

    cout << endl;

    if (FinalTime_ofString == FinalTime_ofChar) {
        cout << " Time is incvivalence" << endl;
    }
    else
    {
    }
    if (FinalTime_ofString > FinalTime_ofChar)
    {
        cout << " Char faster in " << FinalTime_ofString / FinalTime_ofChar << " times" << endl;
    }
    else cout << " String faster in " << FinalTime_ofChar / FinalTime_ofString << " times" << endl;
}
