#include <iostream>
#include <cmath>
using namespace std;

int main()
{
double param, sinus, cosinus, tangens, PI;
char ch;
PI = 3.141592653589793;

do
{
    cout<< " Enter param:\n ";
    cin >>param;
    sinus = sin(param * PI/180);
    cout <<" Sinus of an angel "<< sinus <<endl;
    cosinus = cos(param * PI/180);
    cout <<" Cosinus of an angel "<< cosinus <<endl;
    tangens = tan(param * PI/180);
    cout <<" Tangens of an angel "<< tangens <<endl;      
    cout <<"Введите '1' ,  если хотите продолжить:";
    cin >> a;
} while (ch == 1);
    
    return 0;
}
