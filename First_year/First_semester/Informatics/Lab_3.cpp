#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

int check(){
	int number;
	string inp;
	bool isIncorrect = true;
	
	cout << " Input an upper limit: ";

		while (isIncorrect) {
			getline(cin, inp);

			try {
				number = stoi(inp);
				if ((inp.size() == to_string(number).size()) && ( number > 1 )) {
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

int main()
{
	char ch = 'Y';
	while (ch == 'Y' || ch == 'y') {
		int number, b = 1;
		cout << "=======================================================================================================================" << endl;
		number = check();
		cout << "=======================================================================================================================" << endl;
		vector<int> Prost(number+1);
		for (int i = 0; i < number + 1; i++)
			Prost[i] = i;
		for (int p = 2; p < number + 1; p++)
		{
			if (Prost[p] != 0)
			{
				cout <<" " << Prost[p] << " ";
				for (int j = p * p; j < number + 1; j += p)
					Prost[j] = 0;
			}
		}
		cout << endl;
		/*cin.get(); cin.get();
		cout << endl;*/
		cout << "=======================================================================================================================" << endl;
		cout << endl;
		cout << " Enter 'Y' if you want to continue:" << endl;
		cout << " ";
		cin >> ch;
		cout << endl;
	}

}
