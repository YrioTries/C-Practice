#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace std;

double an(double x, int n) {
    return (pow(-1, n) * pow(2, 2 * n - 1) * pow(x, 2 * n - 1)) / (2 * n - 1);
}
void summaPoN(int n, double x) {
    long double sum = 0;
    for (int i = 1; i < n + 1; i++)
    {
        double ai = an(x, i);
        sum += ai;
        cout << "Номер итерации:" << i << endl;
        cout << "Последний просуммированный член ряда:" << ai << endl;
        cout << "Текущая частичная сумма:" << sum << endl;
        cout << "Точность вычисления заданной текущей частичной суммы:" << long double(abs(abs(an(x, i)) / sum)) << endl;
        cout << endl;
    }
}
void summaPoTochnosti(long double e, double x) {
    double sum = 0;
    long double ai;
    int i = 1;
    while (long double(abs(an(x, i)) / sum) >= e) {
        double ai = an(x, i);
        sum += ai;
        cout << "Номер итерации:" << i << endl;
        cout << "Последний просуммированный член ряда:" << ai << endl;
        cout << "Текущая частичная сумма:" << sum << endl;
        cout << "Точность вычисления заданной текущей частичной суммы:" << long double(abs(abs(an(x, i)) / sum)) << endl;
        cout << endl;
        i++;
    }
}
int main()
{
    int choose = 1;
    setlocale(LC_ALL, "Russian");

    while (choose != 0) {
        double x;
        long double e;
        cout << " Введите x (-1/4 < x <= 1/2): ";
        cin >> x;
        while ((x <= (-0.25) || x > 0.5))
        {
            cout << "Введите х согласно условию -1<=x<=1:";
            cin >> x;
        }
        cout << "Введите точность:";
        cin >> e;
        while (e <= 0) {
            cout << "Точность не может быть не положительной. Введите точность:";
            cin >> e;
        }
        if (e >= 1 && int(e) == e)
        {
            summaPoN(e, x);
        }
        else {
            summaPoTochnosti(e, x);
        }
        cout << endl;
        cout << "Чтобы выйти введите 0. Чтобы повторить расчёт введите 1:";
        cin >> choose;
    }

}
