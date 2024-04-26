#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


int alphabet(vector<char> rN, int i)
{
	switch (rN[i])
	{
	case 'I': return 1;
	case 'V': return 5;
	case 'X': return 10;
	case 'L': return 50;
	case 'C': return 100;
	case 'D': return 500;
	case 'M': return 1000;
	}
	return 0;
}

int fromRomanToInteger(vector <char>& rN, vector <int>& vec, int& nN)
{
	vector <int> newNM;
	int sizeVec = rN.size();
	// перевожу римские цифры (хранятся посимвольно в чаровском векторе) в арабские (будут храниться посимвольно в интовском векторе)
	for (int i = 0; i < sizeVec; ++i)
	{
		int j = alphabet(rN, i);
		vec.push_back(j);
	}
	// начинаю анализировать какие числа стоят, рассматриваю случаи, когда по-римски написаны числа 9(IX), 40(XL), етс
	for (int j = 1; j < (vec.size()); ++j)
	{
		if (vec[j - 1] < vec[j])
		{
			int newNum = vec[j] - vec[j - 1];
			newNM.push_back(newNum);
			rN[j - 1] = ' '; // удаляю из вектора числа формат IX, XL, etc
			rN[j] = ' ';
		}
	}
	// считаю к-во тысяч сотен десятков етс в вектор без чисел формата IX etc
	int countI = 0, countV = 0, countX = 0, countL = 0, countC = 0, countD = 0, countM = 0;
	countI = count(rN.begin(), rN.end(), 'I');
	countV = count(rN.begin(), rN.end(), 'V');
	countX = count(rN.begin(), rN.end(), 'X');
	countL = count(rN.begin(), rN.end(), 'L');
	countC = count(rN.begin(), rN.end(), 'C');
	countD = count(rN.begin(), rN.end(), 'D');
	countM = count(rN.begin(), rN.end(), 'M');

	nN = countM * 1000 + countD * 500 + countC * 100 + countL * 50 + countX * 10 + countV * 5 + countI * 1;
	if (newNM.size() != 0)
	{
		for (int k = 0; k < newNM.size(); ++k)
			nN += newNM[k];
	}
	return 0;
}

int main()
{

	string romanNumber;
	vector <char> romNum;
	vector <int> intNum;
	int newNum;

	cin >> romanNumber;
	int sizeStr = romanNumber.size();
	for (int i = 0; i < sizeStr; ++i)
	{
		romNum.push_back(romanNumber[i]);
	}
	fromRomanToInteger(romNum, intNum, newNum);
	cout << newNum;
}
