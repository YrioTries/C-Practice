#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <cstring>
using namespace std;

// Вариант 3.
// do...while
enum Type { kw, co, ao, id, vl, wl, eq };
// kw - зарезервированные, со - сравнение, ао - арифметика, id - индефикаторы
// vl - константы, wl - мусор, eq - равно
enum State { St, Id, Vl, Sr1, Sr2, Ao, Err, Sr3, Fin };

struct Lex {
    Type type;
    char* str;
};

State stateMatriX[9][8] //Создаём матрицу состояний
{
   // St   Id     Vl   Sr1   Sr2   Ao    Er    Sr3
      Id,  Id,   Err,  Id,   Id,   Id,   Err,  Id,         //Буква латинского алфавита
      Vl,  Id,   Vl,   Vl,   Vl,   Vl,   Err,  Vl,        //Цифры
      Fin, Fin,  Fin,  Fin,  Fin,  Fin,  Fin,  Fin,      //Символы пропуска
      Err, Err,  Err,  Err,  Err,  Err,  Err,  Err,     //Символы, не входящие в алфавит
      Sr1, Sr1,  Sr1,  Sr1,  Sr1,  Err,  Sr1,  Sr1,    //Символ '<'
      Sr2, Sr2,  Sr2,  Sr3,  Sr2,  Err,  Sr2,  Sr2,   //Символ '>'
      Ao,  Ao,   Ao,   Sr3,  Sr3,  Err,  Ao,   Ao,   //Символ '='
      Ao,  Ao,   Ao,   Ao,   Ao,   Err,  Ao,   Ao,  //Символ '+'
      Ao,  Ao,   Ao,   Ao,   Ao,   Err,  Ao,   Ao  //Символ '-'
};

int CharType(char ch) {    // Функция определяющая текущий символ
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

char* PrintTypeL(Lex lexm) {   // Функция вывода типа
    char* type = new char[3];
    if (lexm.type == kw)  strncpy(&type[0], "kw", 3);
    else if (lexm.type == id)  strncpy(&type[0], "id", 3);
    else if (lexm.type == ao)  strncpy(&type[0], "ao", 3);
    else if (lexm.type == co)  strncpy(&type[0], "co", 3);
    else if (lexm.type == vl)  strncpy(&type[0], "vl", 3);
    else if (lexm.type == wl)  strncpy(&type[0], "wl", 3);
    else if (lexm.type == eq)  strncpy(&type[0], "eq", 3);
    return type;
}

void FindLexTypeForUs(Lex& lexy, State state) {  // Функция нахождения типа лексемы
    if (state == Id) {
        if (!strcmp(lexy.str, "do") || !strcmp(lexy.str, "while") || !strcmp(lexy.str, "loop")) lexy.type = kw;  // Если зарезервированные
        else
            strlen(lexy.str) > 5 ? lexy.type = wl : lexy.type = id; // Если длинна слова больше 5, то это мусор, иначе - id            
    }
    else if (state == Vl)
        atoi(lexy.str) > 32767 || atoi(lexy.str) < -327678 ? lexy.type = wl : lexy.type = vl;
    // Если диапазон все границах дозволенного, то это мусор, инче константа    
    else if (state == Sr1 || state == Sr2 || state == Sr3) lexy.type = co; // Проверка на символы сравнения
    else if (state == Err) lexy.type = wl;  // Проверка на мусор
    else if (state == Ao)
        !strcmp(lexy.str, "=") ? lexy.type = eq : lexy.type = ao; // Проверка на >= и <=
}

vector<Lex>* LexAnalysisT(const char* ch_a_text) {
    vector<Lex>* l_v_result = new vector<Lex>();
    int i_curPos = 0;                     // Текущая позиция в строке
    State state = State::St, prevState;  // Текущее и предыдущее состояния
    Lex lexm;                           // Текущая лексема
    int i_firstPos = 0;                // Позиция начала лексемы
    do {
        prevState = state;      // Инициализируем предыдущее состояние
        char ch_curChar = ch_a_text[i_curPos];  // Считываем текущий символ
        if (state == State::St && ch_curChar != ' ' && ch_curChar != '\t' && ch_curChar != '\n' && ch_curChar != '\0')
            i_firstPos = i_curPos;
        state = stateMatriX[CharType(ch_curChar)][state];  // Задаём состояние
        if (state == Fin ||
        (prevState != state && prevState != St && state != Err && !(state == Sr3 && prevState == Sr1) && !(state == Sr3 && prevState == Sr2))
           || (state == Err && prevState == Ao) || (state == Sr2 && prevState == Sr2) || (state == Sr1 && prevState == Sr1)
           || (state == Err && prevState == Sr1) || (state == Err && prevState == Sr2) || (state == Err && prevState == Sr3)) {
            int length = i_curPos - i_firstPos;
            lexm.str = new char[length + 1];
            strncpy(&lexm.str[0], &ch_a_text[0] + i_firstPos, length); // Запись подстроки в лексему
            lexm.str[length] = '\0';
            FindLexTypeForUs(lexm, prevState);  // Присваиваем тип нашей лексеме    
            l_v_result->push_back(lexm);      // Добавляем лексему в вектор
            if (state != Fin)
                --i_curPos;
            else {
                while (ch_a_text[i_curPos + 1] == ' ' || ch_a_text[i_curPos + 1] == '\t' || ch_a_text[i_curPos + 1] == '\n' || ch_a_text[i_curPos + 1] == '\0')
                    ++i_curPos;
            }                     // Если мы добрались до символа пробела/пропуска, то проверяем нет ли пробелов дальше
                                 // Если мы остановились на каком то специальном символе, то мы должны "отодвинуть" позицию назад, чтобы мы опять смогли прочитать этот символ
            state = State::St;  // Возвращение в начальное состояние
        }
    } while (ch_a_text[i_curPos++] != '\0');
    return l_v_result;
}

void printRes(vector<Lex>* l_v_result, ofstream& out) {
    for (int i = 0; i < int(l_v_result->size()); ++i)  // Выводим все лексемы и их типы
        out << l_v_result->at(i).str << "[" << PrintTypeL(l_v_result->at(i)) << "] ";
    out << endl;
    for (int i = 0; i < int(l_v_result->size()); ++i) // Выводим идентификаторы
        if (l_v_result->at(i).type == id)
            out << l_v_result->at(i).str << " ";
    out << endl;
    for (int i = 0; i < int(l_v_result->size()); ++i) // Выводим константы
        if (l_v_result->at(i).type == vl)
            out << l_v_result->at(i).str << " ";
}

int main()
{
    ifstream ifs_fin("input.txt");
    int i_size = 0;
    ifs_fin.seekg(0, ios::end);  // Указатель на начало файла
    i_size = ifs_fin.tellg();
    ifs_fin.seekg(0, ios::beg);  // Указатель на конец файла
    char* ch_a_text = new char[i_size + 1];
    ifs_fin.getline(ch_a_text, i_size + 1, '\0');
    ifs_fin.close();
    if (ch_a_text[0] != '\0') {
        vector<Lex>* l_v_result = LexAnalysisT(ch_a_text);
        ofstream ofs_fout("output.txt");
        printRes(l_v_result, ofs_fout);
        ofs_fout.close();
        for (int i = 0; i < int(l_v_result->size()); ++i)
            delete[] l_v_result->at(i).str;
        delete l_v_result; // Освобождение памяти
        delete[] ch_a_text;
        return 0;
    }
    else return 0;
}
