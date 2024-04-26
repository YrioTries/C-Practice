#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Info
{
private:

	string time;
	int floor_start;
	int floor_finish;

public:

	Info() //Конструктор
	{
		floor_start = 1;
		floor_finish = 1;
	}

	Info(int hours, int minutes, int floor_start, int floor_finish) //Перегрузка конструктора
	{
		
		time = to_string(hours) + ":" + to_string(minutes);
		this -> floor_start = floor_start;
		this -> floor_finish = floor_finish;
	}

	int Count_floors()
	{		
		return abs(floor_finish - floor_start);
	}

	~Info() // Деструктор
	{

	}

	//int GetHour() // Геттер
	//{
	//	return hours;
	//} 
	//
	//void SetHour(int h) // Сеттер
	//{
	//	hours = h;
	//}

	void Print() // Функция принт
	{
		cout << " Время " << time << endl;
		cout << " Этаж " << floor_start << endl;
	}

	friend ostream& operator << (ostream&, const Info&);
	friend istream& operator >> (istream&, Info&);
	friend ofstream& operator << (ofstream&, const Info&);
	friend ifstream& operator >> (ifstream&, Info&);
};

int checking() {
	int w;
	string inp;
	bool isIncorrect = true;

	while (isIncorrect) {
		getline(cin, inp);

		try {
			w = stoi(inp);
			if (inp.size() == to_string(w).size()) {
				isIncorrect = false;
				return w;
			}
			else
				cout << " Ошибка ввода, попробуйте снова: " << endl;
		}
		catch (invalid_argument) {
			cout << " Ошибка ввода, попробуйте снова: ";
		}

	}
}

int prov() // функция для установки месяца
{
	checking();
		
	if (w > 2 || w < 1)
	{
		cout << " Ошибка ввода, нажмите '1' или '2': " << endl;

		checking();
	}

	
	return w;
		
}

int hours_check_ENTER()
{
	checking();

	if ((hours <= 0) || ((hours < 0) || (hours == 24))) {

		cout << " Ошибка ввода, значение минут должно находится в интервале (0<=x<24), попробуйте снова:";

		checking();
	}

	return hours;
	cout << endl;
}


int minutes_check_ENTER()
{
	int minutes;
	string inp;
	bool isIncorrect = true;


	while (isIncorrect) {
		getline(cin, inp);

		try {
			minutes = stoi(inp);
			if (inp.size() == to_string(minutes).size()) {
				isIncorrect = false;
				return minutes;
			}
			else
				cout << " Ошибка ввода, значение минут должно находится в интервале (0<=x<60), попробуйте снова:";
		}
		catch (invalid_argument) {
			cout << " Ошибка ввода, значение минут должно находится в интервале (0<=x<60), попробуйте снова:";
		}

	}
	if ((minutes <= 0) || ((minutes < 0) || (minutes == 60))) {

		cout << " Ошибка ввода, значение минут должно находится в интервале (0<=x<60), попробуйте снова:";

		while (isIncorrect) {
			getline(cin, inp);

			try {
				minutes = stoi(inp);
				if (inp.size() == to_string(minutes).size()) {
					isIncorrect = false;
					return minutes;
				}
				else
					cout << " Ошибка ввода, значение минут должно находится в интервале (0<=x<60), попробуйте снова:";
			}
			catch (invalid_argument) {
				cout << " Ошибка ввода, значение минут должно находится в интервале (0<=x<60), попробуйте снова:";
			}

		}
	}

	return minutes;
	cout << endl;

}


istream& operator >> (istream& in, Info& ride) // перегрузка оператора << istream
{
	int hours, minutes;

	cout << " Часы:";
	/*hours = hours_check_WHILE();*/
	hours = hours_check_ENTER();
	cout << " Минуты:";
	/*minutes = minutes_check();*/
	minutes = minutes_check_ENTER();
	ride.time = to_string(hours) + ':' + to_string(minutes);
	cout << " Начальный этаж:";
	in >> ride.floor_start;
	cout << " Конечный этаж:";
	in >> ride.floor_finish;
	return in;
}

ostream& operator<<(ostream& out, const Info& ride) // перегрузка оператора << istream
{
	out << ride.time << " " << ride.floor_start << " " << ride.floor_finish;
	return out;
}

ifstream& operator >> (ifstream& in, Info& ride) // перегрузка оператора >> ifstream
{
	in >> ride.time >> ride.floor_start >> ride.floor_finish;;
	return in;
}

ofstream& operator<<(ofstream& out, const Info& ride) // перегрузка оператора << ofstream
{
	out << ride.time << " " << ride.floor_start << " " << ride.floor_finish;
	return out;
}



int main()
{
	int choice1, choice2;
	int number;
	ifstream fin;
	ofstream fout;
	string path1 = "Input.txt";
	string path2 = "Output.txt";
	string msg;
	Info Lift;
	vector<Info> VClass; // вектор элементов класса

	setlocale(LC_ALL, "ru");

	cout << " Сделайте выбор: " << endl;
	cout << " Введите '1', если хотите заполнить значения самостоятельно" << endl;
	cout << " Введите '2', если хотите заполнить значениями из файла" << endl;
	cout << endl;
	cout << " ";

	choice1 = prov();
	cout << endl;	

	if (choice1 == 1)
	{

		cout << " Сколько экзепляров классов? " << endl;
		cout << " Количество: ";
		cin >> number;

		cout << " Заполнитe:" << endl;
		for (int i = 0; i < number; i++)
		{
			cout << " N* " << i + 1 << endl;
			cin >> Lift;
			VClass.push_back(Lift);
		}
	}else {

		fin.open(path1);

		if (fin.is_open())
		{
			while (!(fin.eof()))
			{
				fin >> Lift;
				VClass.push_back(Lift);
			}
			
		}
		fin.close();
	}

	cout << " Сделайте выбор: " << endl;
	cout << " Введите '1', если хотите вывести значения в консоль" << endl;
	cout << " Введите '2', если хотите вывести значения в файла" << endl;
	cout << endl;
	cout << " ";

	choice2 = prov();
	cout << endl;
	if (choice2 == 1)
	{
		cout << " Время/Начальный этаж/конечный этаж/Число этажей " << endl;
		for (int i = 0; i < VClass.size(); i++)
		{
			cout << " N*" << i + 1 << " " << VClass[i] << " " << VClass[i].Count_floors() << endl;
		}
	}else{
		fout.open(path2);

		if (fout.is_open())
		{
			fout << " Время/Начальный этаж/конечный этаж/Число этажей " << endl;

			for (int i = 0; i < VClass.size(); i++)
			{
				fout << " N*" << i + 1 << " " << VClass[i] << " " << VClass[i].Count_floors() << endl;
			}
			cout << "Данные обработки успешно выведены" << endl;
			fout.close();
		}
	}	
}
