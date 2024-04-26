#include <iostream>
#include <cmath>
#include <string>
using namespace std;

double check() {
	double number;
	string inp;
	bool isIncorrect = true;

	size_t pos;
	while (isIncorrect) {
		getline(cin, inp);

		try {
			number = stod(inp, &pos);
			if ((inp.size() == pos)) {
				isIncorrect = false;
				return number;
			}
			else
				cout << "\n Error message, try again: ";
		}
		catch (invalid_argument) {
			cout << "\n Error message, try again: ";
		}

	}

	return number;
}
int checkNum() {
	int number;
	string inp;
	bool isIncorrect = true;


	while (isIncorrect) {
		getline(cin, inp);

		try {
			number = stoi(inp);
			if ((inp.size() == to_string(number).size()) && (number >= 1)) {
				isIncorrect = false;
				return number;
			}
			else
				cout << "\n Error message, try again: ";
		}
		catch (invalid_argument) {
			cout << "\n Error message, try again: ";
		}

	}


	return number;
	cout << endl;
}

double oper()
{
	int number;
	long double Sum1 = 0, Sum = 0;
	double first, point;

	cout << " =========================================" << endl;
	cout << " Input a start value:" << endl;
	cout << " ";
	first = check();


	cout << " =========================================" << endl;
	cout << " Input a common ratio:"<< endl;
	cout << " ";
	point = check();


	cout << " =========================================" << endl;
	cout << " Input the number of elements:" << endl;
	cout << " ";

	number = checkNum();


	Sum = (first * (pow(point, number) -1)) / (point -1);

	return Sum;
}

int main()
{
	char ch = 'y';

	while (ch == 'Y' || ch == 'y')
	{

		long double Sum;

		Sum = oper();

		cout << " =========================================" << endl;
		cout << " Result: " << Sum << endl;

		cout << " Do you want to continue? " << endl;
		cout << " Enter 'Y', if you want to continue: " << endl;
		cout << " ";
		cin >> ch;
		cout << endl;

	}
}
