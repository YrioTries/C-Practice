#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <ctype.h>
using namespace std;

enum ELexType { Do, Wh, Id2, Vl2, Co, Eq, Ao2, Loop, Wl };
// Строковые представления лексем
char TYPE_NAMES[9][3] = { "do", "wh", "id", "vl", "co", "eq", "ao", "lp", "wl" };
enum EState { S, Id, Vl, Sr1, Sr2, Ao, E, Min, Sr3, F };//перечисление состояний лексического анализатора
enum EState2 { S2, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, E2 };//перечисление состояний синтаксического анализатора
struct lex {
    ELexType type;//поле отвечающее за тип
    char* str; // текст лексемы
};
EState matrix[9][9] //Создаём матрицу состояний для лексического анализатора
{
    //  S   Id  Vl  Sr1 Sr2 Ao E  Min  Sr3
      Id, Id, E,  Id, Id, Id,E,  Id, Id,      //Буква латинского алфавита
      Vl, Id, Vl, Vl, Vl, Vl,E,  Vl, Vl,     //Цифры
      F,  F,  F,  F,  F,  F, F,  F,  F,      //Символы пропуска
      E,  E,  E,  E,  E,  E, E,  E,  E,      //Символы, не входящие в алфавит
      Sr1,Sr1,Sr1,Sr1,Sr1,E, Sr1,Sr1,Sr1,    //'<'
      Sr2,Sr2,Sr2,Sr3,Sr2,E, Sr2,Sr2,Sr2,    //'>'
      Ao, Ao, Ao, Sr3,Sr3,E, Ao, Ao, Ao,     //=
      Ao, Ao, Ao, Ao, Ao, E, Ao, Ao, Ao,     //+
      Min,Ao, Ao, Min,Min,E, Min,Ao, Ao      //-
      /*(Min)*/ /*Min,Min,E, Min*/
                   /*Ao, Ao, E, Ao*/
        /*Данная таблица создавалась так, чтобы она учитывала и отрицательные числа, в связи с этим есть такое состояние как Min
        Однако сейчас она изменена и работает только на положительные, но Min я решил оставить, чтобы если что проверить как программа может
        работать на отрицательных*/
};
EState2 matrix2[11][10] //Создаём матрицу состояний для синтаксического анализатора
{
    //S2  A1  A2  A3  A4  A5  A6  A7  A8  A9  A10
      A1, E2, E2, E2, E2, E2, E2, E2, S2, E2, S2,  //do
      E2, E2, E2, E2, E2, E2, A7, E2, E2, E2, E2,  //while
      E2, A2, E2, A4, A5, A4, E2, A8, E2, A10,E2,   //id
      E2, E2, E2, E2, A5, A4, E2, E2, E2, A10,E2,   //vl
      E2, E2, E2, E2, E2, E2, E2, E2, A9, E2, E2,  //co
      E2, E2, A3, E2, E2, E2, E2, E2, A9, E2, E2,  //eq
      E2, E2, E2, E2, E2, E2, E2, E2, E2, E2, A9,  //ao
      E2, E2, E2, E2, A6, E2, E2, E2, E2, E2, E2,  //loop
      E2, E2, E2, E2, E2, E2, E2, E2, E2, E2, E2   //wl
};

int type_curchar(char ch) {    // Функция определяющая текущий символ
    if (isalpha(ch)) return 0;
    else if (isdigit(ch)) return 1;
    else if (isspace(ch) || iscntrl(ch)) return 2;
    else if (ch == '<') return 4;
    else if (ch == '>') return 5;
    else if (ch == '=') return 6;
    else if (ch == '+') return 7;
    else if (ch == '-') return 8;
    else return 3;
}
void type(lex& lexema, EState state) {//по состоянию лексемы находим её тип

    if (state == Id) {
        if (!strcmp(lexema.str, "do")) lexema.type = Do;
        else {
            if (!strcmp(lexema.str, "while")) lexema.type = Wh;
            else {
                if (!strcmp(lexema.str, "loop")) lexema.type = Loop;
                else {
                    if (strlen(lexema.str) > 5) lexema.type = Wl;
                    else lexema.type = Id2;
                }
            }
        }
    };
    if (state == Vl) {
        if (atoi(lexema.str) > 32767 || atoi(lexema.str) < -32768) lexema.type = Wl;
        else lexema.type = Vl2;
    };
    if (state == Sr1 || state == Sr2 || state == Sr3) lexema.type = Co;
    if (state == E) lexema.type = Wl;
    if (state == Min || state == Ao) {
        if (!strcmp(lexema.str, "=")) lexema.type = Eq;
        else lexema.type = Ao2;
    }
}

vector<lex>* LexAnalysis(const char* text)
{
    vector<lex>* result = new vector<lex>();
    int position = -1; // текущая позиция в строке
    EState state = EState::S, prevState, lastState = S;// lastState = S; // текущее состояние
    lex lexema; // текущая лексема
    int firstPos; // позиция начала лексемы
    do//пока не дойдём до конца файла
    {
        prevState = state;//инициализируем предыдущее состояние
        position++;//переходим на другую позицию
        char currentChar = text[position];//считываем текущий символ
        // Инициализация лексемы при обнаружении непробельного символа
        if (state == EState::S && currentChar != ' ' && currentChar != '\t' && currentChar != '\n' && currentChar != '\0')
        {
            firstPos = position;
        }
        if (lastState == Vl && currentChar == '-') state = Ao; //   Данное условие также нужно лишь для работы с отрицательными числами
        else                                                    // Оно позволяет записать "2-3" как "2[co] -[ao] 3[co]" а не как "2[co] -3[co] 
            state = matrix[type_curchar(currentChar)][state];//проверяем наше состояние
        //если мы дошли до символа пробела или символа разделителя или до определенного случая
        if (state == F ||
        (prevState != state && prevState != S && state != E && !(state == Vl && prevState == Min) && !(state == Sr3 && prevState == Sr1) && !(state == Sr3 && prevState == Sr2))
         ||  (state == E && prevState == Ao)  || (state == Sr2 && prevState == Sr2) || (state == Sr1 && prevState == Sr1)
         ||  (state == E && prevState == Sr1) || (state == E && prevState == Sr2)   || (state == E && prevState == Sr3)) {

            int length = position - firstPos;//находим длину лексемы, которую будем записывать
            lexema.str = new char[length + 1];
            // Вычленение подстроки и запись в лексему
            strncpy(&lexema.str[0], &text[0] + firstPos, length);
            lexema.str[length] = '\0';
            type(lexema, prevState);//присваиваем тип нашей лексеме
            // Запись лексемы в список
            result->push_back(lexema);

            if (state != F) position--;
            else {
                if (text[position] == '\0') return result;
                else {
                    while (text[position + 1] == ' ' || text[position + 1] == '\t' || text[position + 1] == '\n' || text[position + 1] == '\0')
                        position++;
                }
            } //если мы добрались до символа пробела/пропуска, то проверяем нет ли пробелов дальше
          //если мы остановились на каком то специальном символе, то мы должно "отодвинуть" позицию назад, чтогбы мы опять смогли прочитать этот символ
            state = S;//обновляем состояние 
        }
        lastState = prevState;//навсякий случай сохраняем состояние лексемы в lastState(нужно для работы с отрицательными числами)

    } while (text[position] != '\0');
    return result;//возвращаем список лексем
}
vector<lex>* Synthax_Analysis(vector<lex>* vec, int& CURPOS) {
    // Вектор лексем, которые ожидались (для вывода ошибки)
    vector<lex>* err = new vector<lex>();
    EState2 state2 = S2;//создаём первоначальное состояние для автомата
    EState2 prevState2; //создаём переменную хранящую предыдущее состояние
    while (state2 != E2 && CURPOS < int(vec->size())) { //пока состояние не ошибочное и мы не дошли до конца вектора проверяем лексемы
        prevState2 = state2; //сохраняем состояние
        state2 = matrix2[vec->at(CURPOS).type][state2];
        CURPOS++; //увеличиваем счётчик
    }
    --CURPOS;//уменьшаем счётчик, т.к. он показывал позицию на одну больше 
    if (state2 != E2 && state2 != A10) {// если конструкция оборвалась и закончена
        prevState2 = state2; //сохраняем финальное состояние
        state2 = E2; // объявляем состояние ошибки
        ++CURPOS; //обратно увеличиваем счётчик, чтобы он указывал на правильную позицию 
    }
    if (state2 == E2) {//для каждого случая обозначаем список лексем, которые следует поставить на эти места
        switch (prevState2) {
        case S2:
            err->push_back(lex({ Do }));
            break;
        case A1:
            err->push_back(lex({ Id2 }));
            break;
        case A2:
            err->push_back(lex({ Eq }));
            break;
        case A3:
            err->push_back(lex({ Id2 }));
            err->push_back(lex({ Vl2 }));
            break;
        case A4:
            err->push_back(lex({ Id2 }));
            err->push_back(lex({ Vl2 }));
            err->push_back(lex({ Loop }));
            break;
        case A5:
            err->push_back(lex({ Id2 }));
            err->push_back(lex({ Vl2 }));
            break;
        case A6:
            err->push_back(lex({ Wh }));
            break;
        case A7:
            err->push_back(lex({ Id2 }));
            break;
        case A8:
            err->push_back(lex({ Do }));
            err->push_back(lex({ Co }));
            err->push_back(lex({ Eq }));
            break;
        case A9:
            err->push_back(lex({ Id2 }));
            err->push_back(lex({ Vl2 }));
            break;
        case A10:
            err->push_back(lex({ Do }));
            err->push_back(lex({ Ao2 }));
            break;
        default:
            break;
        }

    }
    return err;
};
int main()
{
    setlocale(0, ".1251");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    int size = 0;//создаём переменную отвечающую за размер исходного текста
    int CURPOS = 0;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    if (fin) { //проверяем возможность открытия файла
        fin.seekg(0, ios::end);
        size = fin.tellg();//считываем количество символов
        fin.seekg(0, ios::beg);//возвращаем позицию чтения в начало файла
        char* text = new char[size + 1];//создаём динамический массив 
        fin.getline(text, size + 1, '\0');//и заполняем его нашим текстом
        text[size] = '\0';
        if (text[0] != '\0') {//если текст непустной начинаем его анализировать
            vector<lex>* list_lex = LexAnalysis(text);//создаём указатель на вектор, который пример вектор лексем
            vector<lex>* err_synthax = Synthax_Analysis(list_lex, CURPOS);
            if (fout) {
                for (int i = 0; i < int(list_lex->size()); ++i) {//выводим все лексемы и их типы
                    fout << list_lex->at(i).str << "[" << TYPE_NAMES[list_lex->at(i).type] << "] ";
                    cout << list_lex->at(i).str << "[" << TYPE_NAMES[list_lex->at(i).type] << "] ";
                }
                fout << endl;
                cout << endl;
                if (err_synthax->size()) {//если вектор с исправляющими лексемами непустой
                    if (CURPOS == 1) {
                        cout << "OK";
                        fout << "OK";
                    }
                    else {
                        cout << CURPOS << " "; //выводим позицию с которой сломалась конструкция
                        fout << CURPOS << " ";
                        for (int i = 0; i < int(err_synthax->size()); ++i) {

                            fout << TYPE_NAMES[err_synthax->at(i).type] << " "; //выводим типы которые могли стоять на этом месте
                            cout << TYPE_NAMES[err_synthax->at(i).type] << " ";

                        }
                    }
                    

                }
                else { //в случае, если все верно выводим ОК
                    cout << "OK";
                    fout << "OK";
                }
            }
            for (int i = 0; i < int(list_lex->size()); ++i) { //чистим поля str
                delete[] list_lex->at(i).str;
            }

            delete[] text;
            delete list_lex;
            delete err_synthax;
        }
        else {// в случае если строка пустая 
            cout << endl << "0 do";
            fout << endl << "0 do";
        }
    }
    fin.close(); fout.close();

    return 0;
}
