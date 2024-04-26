#include <iostream> 
#include <fstream>
using namespace std;

int* Matrix_Master(int* d_a_param, int const file_size) {
	int cur = 2; // Положение первого элемента матрицы в массиве (без учёта количества столбцов и строчек)

	// Нахождение количества строчек и столбцов
	int m_rows = d_a_param[0];
	int m_cols = d_a_param[1];

	int* d_a_TRmatrix = new int[file_size - 2]; // Создание массива для хранения траспонированной матрицы ([file_size - 2] без учёта количества строк и столбцов)

	
	int** d_a_matrix = new int* [m_rows]; // Создание двумерного массива для исходной матрицы
	for (int i = 0; i < m_rows; i++) {
		d_a_matrix[i] = new int[m_cols];
	}

	for (int j = 0; j < m_rows; j++) { // Переносим информацию из масива в матрицу
		cout << endl;
		for (int i = 0; i < m_cols; i++) {
			d_a_matrix[j][i] = d_a_param[cur];
			cout << d_a_matrix[j][i] << " ";
			cur++;
		}
	}

	cur = 0; // Присваиваем ноль, т.к записываем в пустой массив с первого (нулевого) элемента

	cout << endl;

	for (int i = 0; i < m_cols; i++) {
		cout << endl;
		for (int j = 0; j < m_rows; j++) {
			d_a_TRmatrix[cur] = d_a_matrix[j][i]; // Транспонируем матрицу, записываем в массив
			cout << d_a_TRmatrix[cur] << " ";
			cur++;
		}
	}

	for (int i = 0; i < m_rows; i++) {
		delete[] d_a_matrix[i]; // Освобождение памяти
	}
	delete[] d_a_matrix; // Освобождение памяти

	return d_a_TRmatrix; // Возвращаем d_a_TRmatrix
}

int main()
{
	ifstream ifs_fin("input.txt"); // Создание объекта ifstream
	int file_size = 0; // Переменная размера файла
	int arg_f;// Переменная необходимая, чтобы найти размер файла

	while (ifs_fin >> arg_f) file_size++; // Определяем число элементов массива
	ifs_fin.close(); ifs_fin.open("input.txt"); // Переоткрываем файл для повторного чтения
	int* d_a_param = new int[file_size]; // Массив для записи входных данных

	for (int i = 0; i < file_size; ++i) { // Считываем информацию с файла
		ifs_fin >> d_a_param[i];
	}

	ifs_fin.close(); // Закрытие файла

	if (d_a_param[0] * d_a_param[1] != file_size - 2) {
		cout << "nuber of digit in matrix is uncorrect";
		return 0;
	}

	int* d_a_TRmatrix = new int[file_size - 2]; // Создание массива для хранения траспонированной матрицы ([file_size - 2] без учёта количества строк и столбцов)

	d_a_TRmatrix = Matrix_Master(d_a_param, file_size); // Используем функцию

	delete[] d_a_param; // Освобождаем память

	ofstream ofs_fout("output.txt"); // Создание объекта ofstream

	for (int i = 0; i < file_size - 2; i++) { // Записываем в файл			
		ofs_fout << d_a_TRmatrix[i] << " ";
	}

	ofs_fout.close(); // Закрытие файла

	delete[] d_a_TRmatrix; // Освобождение памяти

	return 0;
}
