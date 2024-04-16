#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string chvecs, snums, e, correct = " ";
    bool first = true, letter = false, degree = false;
    double dd, ed, en, numberd, sum = 0;


    ifstream fn; // Создание объекта класса ifstream (файловый ввод)
    fn.open("input.txt"); // Связывание объекта с файлом

    if (!fn.is_open()) // Проверка на корректное открытие файла
    {
        cout << " Error! File was not opened " << endl;
        cout << " Check if txt file exist " << endl;
    }

    cout << "======================================================================" << endl;
    cout << " Given array" << endl;
    cout << "======================================================================" << endl;

    while (!fn.eof()) // Заполняем строку из файла
    {
        chvecs = " ";
        getline(fn, chvecs);
        cout << chvecs << endl;
    }

    fn.close();

    if (chvecs[chvecs.size() - 1] != ' ') {
        chvecs += correct;
    }

    for (unsigned int i = 0; i <= chvecs.size() - 1; i++) {

        if (isalpha(chvecs[i])) { // Проверка на буквы
            if (chvecs[i] == 'e') {
                degree = true;  // Если буква е, то присваеваем значение "правда" булевой переменной степени
            }
            else {
                letter = true; // Если это другая буква выходим из цикла
                break;
            }

        }
        else {
            if (chvecs[i] != ' ') {

                if (degree) { // 
                    e.push_back(chvecs[i]); // Записываем степень в строку
                }
                else {
                    snums.push_back(chvecs[i]); // Записываем число в строку
                }

            }
            else {
                if (!(chvecs[i - 1] == ' ' && chvecs[i] == ' ')) {
                    if (first)
                    {
                        dd = stod(snums); // Переводим строку в число "d"
                        first = false;

                        if (degree) {
                            ed = stod(e); // Переводим строку степень числа "d"                         
                            dd = pow(dd, ed);
                            first = false;
                            degree = false;
                        }


                    }
                    else {
                        numberd = stod(snums); // Переводим строку в число                        

                        if (degree) { // Если число имеет степень
                            en = stod(e); // Переводим строку в значение степени                         
                            numberd = pow(numberd, en);
                            degree = false;
                        }
                        if (dd < 0) { // Если число d (double d) меньше нуля
                            if (numberd <= dd && numberd < 0) {
                                sum += numberd; // Суммирование
                            }
                        }
                        else { // Если число d (double d) больше нуля
                            if (numberd < 0) { 
                                sum += numberd; // Суммирование
                            }
                        }

                    }
                    degree = false;
                    snums.clear(); // Пользуемся методом, чтобы отчистить строку
                    e.clear();
                }

            }
        }

    }

    ofstream ft;  // Создание объекта класса ofstream (файловый вывод)
    ft.open("output.txt"); // Связывание объекта с файло


    if (letter) {
        ft << " File filling arror \n There are letters in it"; // Передача в файл 
        cout << "======================================================================" << endl;
        cout << " File filling arror \n There are letters in it" << endl;
        cout << "======================================================================" << endl;
    }
    else {
        cout << "======================================================================" << endl;
        cout << " Sum: " << sum << endl;
        cout << "======================================================================" << endl;
        ft << sum; // Передача значения в файл 

    }

    ft.close();

}
