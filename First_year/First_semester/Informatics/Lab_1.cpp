#include <iostream>
#include <string>
#include <ctype.h>
#include <math.h>
#include <cctype>
#include <stdio.h>
#include <conio.h>
#include <vector>
using namespace std;

int HEX_TO_DEC(char st[10])
{
    int k, p;
    long long sum;
    sum = 0;
    p = strlen(st) - 1;
    for (int i = 0; st[i] != '\0'; i++)
    {
        switch (toupper(st[i])) // Преобразует строчные буквы в прописные
        {
        case 'A': k = 10; break;
        case 'B': k = 11; break;
        case 'C': k = 12; break;
        case 'D': k = 13; break;
        case 'E': k = 14; break;
        case 'F': k = 15; break;
        case '1': k = 1; break;
        case '2': k = 2; break;
        case '3': k = 3; break;
        case '4': k = 4; break;
        case '5': k = 5; break;
        case '6': k = 6; break;
        case '7': k = 7; break;
        case '8': k = 8; break;
        case '9': k = 9; break;
        case '0': k = 0; break;
        }
        sum += k * pow(16, p); // Формула перевода из Hex в Dec
        p--;
    }
    cout << sum << endl;
    return 0;
}

bool is_hex(const string& s) {
    string::const_iterator i; // Итератор для string
    for (i = s.begin(); i != s.end(); ++i) { // Используем методы begin и end
        if (!isxdigit(*i)) // Mакрос возвращающий ненулевое значение, если  аргумент ch является цифрой
            return false;
    }
    return true;
}

int main()
{
    char ch = 'y';

    while (ch == 'Y' || ch == 'y')
    {
        char s[10];
        cout << " ====================================" << endl;
        cout << " Plese, enter string: "<<endl;
        cout << " ";
        cin >> s;
        while (!is_hex(s))
        {
            cout << " ************************************" << endl;
            cout << " ERROR. Try again: ";
            cout << " ";
            cin >> s;
            cout << endl;
            cout << " ************************************" << endl;
        }
        cout << " ====================================" << endl;
        cout << " Result: ";
        HEX_TO_DEC(s); // Используем нашу функцию
        cout << " ====================================" << endl;

        cout << " Enter 'Y' if you want to continue:" << endl;
        cout << " ";
        cin >> ch;
        cout << endl;
    }
}
