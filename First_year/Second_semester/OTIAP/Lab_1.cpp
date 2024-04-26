#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<char*> WordMaster(const char* const ch_a_text) {
	vector<char*> list_slov;
	char* ch_a_word = new char[100]; // Составляемое слово слово
	int current = 0, i_flag = 1; // Текущая позиция в слове
	bool b_number = false, b_letter = false; // Создание булевых переменных для обозначения вхождения в слово букв и цифр

	for (int i = 0; i < 100; ++i) {

		if (ch_a_text[i] == 'A' || ch_a_text[i] == 'B' || ch_a_text[i] == 'C' // Проверка на содержание букв в слове (хотя бы одной)
			|| ch_a_text[i] == 'D' || ch_a_text[i] == 'E' || ch_a_text[i] == 'F'
			|| ch_a_text[i] == 'G' || ch_a_text[i] == 'H' || ch_a_text[i] == 'I'
			|| ch_a_text[i] == 'J' || ch_a_text[i] == 'K' || ch_a_text[i] == 'L'
			|| ch_a_text[i] == 'M' || ch_a_text[i] == 'N' || ch_a_text[i] == 'O'
			|| ch_a_text[i] == 'P' || ch_a_text[i] == 'Q' || ch_a_text[i] == 'R'
			|| ch_a_text[i] == 'S' || ch_a_text[i] == 'T' || ch_a_text[i] == 'U'
			|| ch_a_text[i] == 'V' || ch_a_text[i] == 'W' || ch_a_text[i] == 'X'
			|| ch_a_text[i] == 'Y' || ch_a_text[i] == 'Z' || ch_a_text[i] == 'a'
			|| ch_a_text[i] == 'b' || ch_a_text[i] == 'c' || ch_a_text[i] == 'd'
			|| ch_a_text[i] == 't' || ch_a_text[i] == 'f' || ch_a_text[i] == 'g'
			|| ch_a_text[i] == 'h' || ch_a_text[i] == 'i' || ch_a_text[i] == 'j'
			|| ch_a_text[i] == 'k' || ch_a_text[i] == 'l' || ch_a_text[i] == 'm'
			|| ch_a_text[i] == 'n' || ch_a_text[i] == 'o' || ch_a_text[i] == 'p'
			|| ch_a_text[i] == 'q' || ch_a_text[i] == 'r' || ch_a_text[i] == 's'
			|| ch_a_text[i] == 't' || ch_a_text[i] == 'u' || ch_a_text[i] == 'v'
			|| ch_a_text[i] == 'w' || ch_a_text[i] == 'x' || ch_a_text[i] == 'y'
			|| ch_a_text[i] == 'z') {
			b_letter = true;
		}
		if (ch_a_text[i] == '1' || ch_a_text[i] == '2' || ch_a_text[i] == '3' // Проверка на содержание чисел в слове (хотя бы одного)
			|| ch_a_text[i] == '4' || ch_a_text[i] == '5' || ch_a_text[i] == '6'
			|| ch_a_text[i] == '7' || ch_a_text[i] == '8' || ch_a_text[i] == '9') {
			b_number = true;
		}
		if (ch_a_text[i] == ' ' || ch_a_text[i] == '\n' || ch_a_text[i] == '\t' || ch_a_text[i] == '\0') { // Если слово разделено
			// Проверка слова на соответствие заданию

			if (b_number && b_letter && i_flag <= 6) { // Если слово подходит по условию происходит его запись
				ch_a_word[current] = 0;
				list_slov.push_back(ch_a_word); // Добавление слова в список
				ch_a_word = new char[100];
			}
			current = 0; // Сброс текущей позиции в слове на начало
			i_flag = 0; // Сброс текущего размера слова
			b_number = false; // Сброс булевых переменных
			b_letter = false;
		}
		else {
			ch_a_word[current++] = ch_a_text[i]; // Перемещение по символам слова
			i_flag++; // Увеличение размера слова
		}
	}
	delete[] ch_a_word; // Освобождаем память
	return list_slov; // Возвращаем вектор
}
int main()
{
	ifstream ifs("input.txt");
	ofstream ofs("output.txt");
	// Чтение текста из файла
	char text[100];
	ifs.getline(text, 100, '\0');
	// Обработка текста
	vector<char*> list = WordMaster(text);
	// Вывод результата в консоль и файл
	for (int i = 0; i < list.size(); ++i) {
		cout << list[i] << ' ';
		ofs << list[i] << ' ';
	}
	ifs.close();
	ofs.close();
	return 0;
}
