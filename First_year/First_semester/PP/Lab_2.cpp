#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

const double PI = 3.14;

double checkelements()
{
	int a;
	while (!(cin >> a) || (cin.peek() != '\n')) // ждёт табуляции
	{
		cin.clear(); // отчищает флаги ошибок
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // проверяет весь поток посимвольно
		cout << endl;
		cout << " Error of enter, try again:" << endl;
		cout << " ";
	}
	return a;
}

double fact(int n)
{
	if (n < 0)
		return 0;
	if (n == 0)
		return 1;
	else
		return n * fact(n - 1);
}

double CurrentAn(double x, int n)
{
	return (pow(2, n / 2) * sin(PI * n / 4) * pow(x, n) / fact(n));
}

double CurrentAn(double x, double n)
{
	return (pow(2, n / 2) * sin(PI * n / 4) * pow(x, n) / fact(n));
}

double CurrentAn(float a, float b)
{
	return (pow(2, b / 2) * sin(PI * b / 4) * pow(a, b) / fact(b));
}


int main()
{
	setlocale(LC_ALL, "Rus");//подключение русского текста

	char ans;
	double predX = 10000000;//рандомное значение
	vector <double> An;
	vector <double> Sn;
	vector <double> En;

	do
	{

		cout << " Enter x: \n ";
		double x = checkelements();
		cout << endl;


		cout << " Enter a: \n ";
		double a = checkelements();
		cout << endl;

		while (a < 0)
		{
			cout << " Incorrect input " << endl;
			a = checkelements();
		}



		if (a == int(a))//если а - целое число и обозначает число слагаемых ряда для суммирования
		{
			if (x == predX)// если значение х совпадает с предыдущим
			{
				cout << " The value of x is the same as the privious ones" << "\n" << " Fetched values from memory: " << "\n";

				if (size(Sn) >= a)// если не нужно рассчитывать доп значения
				{
					for (int n = 1; (n <= a); n++)
					{
						cout << " Nuber of iteration: " << n << endl; // вывод всех требуемых значений в консоль
						cout << " An: " << An[n - 1] << endl;
						cout << " Sn: " << Sn[n - 1] << endl;
						cout << " e: " << En[n - 1] << endl;
						cout << "\n";

					}
				}

				else//если нужно рассчитать доп значения
				{
					for (int n = 1; n <= size(Sn); n++)//выведем то, что есть
					{
						cout << " Nuber of iteration: " << n << endl; // вывод всех требуемых значений в консоль
						cout << " An: " << An[n - 1] << endl;
						cout << " Sn: " << Sn[n - 1] << endl;
						cout << " e: " << En[n - 1] << endl;
						cout << "\n";

					}

					cout << " Calculate the ramaining values: " << "\n";// досчитаем оставшиеся
					double S = Sn[size(Sn) - 1];//изначальная сумма = её значению на предыдущем шаге
					double an, n1, en;

					for (int(n) = size(Sn) + 1; n <= a; ++n)// начинаем с того, на чем остановились+1
					{
						an = CurrentAn(x, n);//Аn - значение текущего члена последовательности
						S = S + an;//сумма членов последовательности до n-ого
						n1 = CurrentAn(x, n + 1);// значение (n+1)
						en = abs(n1 / S);// значение текущей точность вычислений

						cout << " Nuber of iteration: " << n << endl; // вывод всех требуемых значений в консоль
						cout << " An: " << an << endl;
						cout << " Sn: " << S << endl;
						cout << " e: " << en << endl;
						cout << "\n";

						An.push_back(an);// добавляем к векторам рассчитанные значения
						Sn.push_back(S);
						En.push_back(en);
					}

				}
			}

			else
			{
				double S = 0;
				double an, n1, en;

				An.clear();// очищаем вектора
				Sn.clear();
				En.clear();

				for (int(n) = 1; n <= a; ++n)//n - номер текущего члена последовательности
				{
					an = CurrentAn(x, n);//Аn - значение текущего члена последовательности
					n1 = CurrentAn(x, n + 1);// значение (n+1)
					S = S + an;//сумма членов последовательности до n-ого
					en = abs(n1 / S);// значение текущей точность вычислений

					cout << " Nuber of iteration: " << n << endl; // вывод всех требуемых значений в консоль
					cout << " An: " << an << endl;
					cout << " Sn: " << S << endl;
					cout << " e: " << en << endl;
					cout << "\n"; 

					predX = x;//обновляем переменную предыдущего значения
					An.push_back(an);
					Sn.push_back(S);
					En.push_back(en);
				}
			}
		}

		else // если а - дробное число и обозначает точность вычислений
		{
			if (x == predX)
			{
				cout << " The value of x is the same as the privious ones" << "\n" << " Fetched values from memory: " << "\n";

				if (En[size(En) - 1] <= a)
				{
					int n = 0;

					do
					{
						cout << " Nuber of iteration: " << n + 1 << endl;
						cout << " An: " << An[n] << endl;
						cout << " Sn: " << Sn[n] << endl;
						cout << " e: " << En[n] << endl;
						cout << "\n";

						n++;

					} while (En[n - 1] >= a);
				}

				else
				{
					for (int n = 1; n <= size(Sn); n++)
					{
						cout << " Nuber of iteration: " << n << endl;
						cout << " An: " << An[n - 1] << endl;
						cout << " Sn: " << Sn[n - 1] << endl;
						cout << " e: " << En[n - 1] << endl;
						cout << "\n";

					}
					cout << " Calculate the ramaining values: " << "\n";

					double S = Sn[size(Sn) - 1];//изначальная сумма = её значению на предыдущем шаге
					double an, n1, en;
					int n = size(Sn) + 1;

					do
					{
						an = CurrentAn(x, n);//Аn - значение текущего члена последовательности
						S = S + an;
						n1 = CurrentAn(x, n + 1);// значение (n+1)
						en = abs(n1 / S);// значение текущей точность вычислений

						cout << " Nuber of iteration: " << n << endl;
						cout << " An: " << an << endl;
						cout << " Sn: " << S << endl;
						cout << " e: " << en << endl;
						cout << "\n";

						n++;

						An.push_back(an);
						Sn.push_back(S);
						En.push_back(en);

					} while (en >= a);
				}
			}

			else
			{
				double S = 0;
				double an, n1, en;
				int n = 1;

				An.clear();
				Sn.clear();
				En.clear();

				do
				{
					an = CurrentAn(x, n);//Аn - значение текущего члена последовательности
					n1 = CurrentAn(x, n + 1);// значение (n+1)
					S = S + an;//сумма членов последовательности до n-ого
					en = abs(n1 / S);// значение текущей точность вычислений

					cout << " Nuber of iteration: " << n << endl;
					cout << " An: " << an << endl;
					cout << " Sn: " << S << endl;
					cout << " e: " << en << endl;
					cout << "\n";

					predX = x;

					An.push_back(an);
					Sn.push_back(S);
					En.push_back(en);
					n++;

				} while (en >= a); // пока значение текущей точность вычислений не станет меньше или равным желаемой точность вычислений
			}

		}

		cout << " Do you want to continue? (Y/N) " << endl;
		cout << " ";
		cin >> ans;
		cout << endl;

	} while (ans == 'Y' || ans == 'y');
}
