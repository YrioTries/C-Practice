#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	vector <char> vec; //вектор для хранения значений из файла

	ifstream fin; //создание объекта класса ifstream (файловый ввод)

	fin.open("MyFile_input.txt"); //связывание объекта с файлом

	if (!fin.is_open()) //проверка на корректное открытие файла
	{
		cout << "Ошибка! Файл не был открыт" << endl;
	}
	else
	{
		cout << "Файл был успешно открыт" << endl;
	}

	char symbol; //переменная типа char
	char prov = ' '; //символ, частоту встречаемости которого надо вычислить
	int j = 0; //переменная которая запоминает позицию искомого символа

	int k = 0; //переменная счётчика

	for (int i = 0; i < vec.size(); i++) //цикл поиска этого символа в самом файле, по принципу того, что он стоит после перевода строки
	{
		if ((i != 0) && (vec[i - 1] == '\n'))
		{
			prov = vec[i];
			j = i;
		}
	}

	while (fin.get(symbol)) //пока в файле есть символы, файл посимвольно добавляется в вектор
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

		vec.push_back(symbol);
	}
	fin.close();



	for (int i = 0; i < (j - 1); i++) //поиск и подсчёт количества повторений нужного символа
	{

		if (vec[i] == prov)
		{
			k += 1;
		}
	}

	ofstream fout; //создание объекта класса ofstream (файловый вывод)

	fout.open("MyFile_output.txt"); //связывание объекта с файлом
	fout << " \nNumber of occurences of a number in the data array: " << k; //передача значения в файл
	fout.close();

}
