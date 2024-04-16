#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// Вариант 3.
// Словом текста является последовательнось букв и цифр. Найти те слова, в которые состоят хотябы из одной буквы и одной цифры, длина слов не более 6 элементов.
//
struct  Lex // структура лексемы
{
    char* word;
    bool word_fitting;
};

ofstream& operator<<(ofstream& out, const Lex& lexem) // перегрузка вывода лексемы в файл
{
    out << lexem.word;
    return out;
}

ostream& operator<<(ostream& out, const Lex& lexem) // перегрузка вывода лексемы в файл
{
    out << lexem.word;
    return out;
}

enum AState { Start, ExpectD, ExpectL, Fine, Error, Final }; // состояния

AState stateMatrix[4][5] // матрица переходов
{
    // Start    ExpectD  ExpectL Fine Error  
   //    0         1       2      3     4  
       ExpectL, Fine,   ExpectL,Fine, Error,   // Цифра
       ExpectD, ExpectD, Fine,  Fine, Error,  // Буква  
       Final,   Final,  Final,  Final,Final, // символы выхода
       Error,   Error,  Error,  Error,Error,// Некорректные символы
};

void LexAnalysis(char* text, int size, vector <Lex>& res) // лексический анализатор
{
    int cur_pos = 0; // текущая позиция в файле
    AState state = AState::Start; // устанавливаем изначальное состояние
    Lex lexem;
    lexem.word_fitting = false;
    int first_pos;
    int end = size + 1;
    bool UNsym = true;

    while (cur_pos != end)
    {
        char curChar = text[cur_pos];

        if (state == AState::Start && curChar != ' ' && curChar != '\t' && curChar != '\n' && curChar != '\r' && curChar != '\0')
        {
            first_pos = cur_pos;
            lexem.word_fitting = false;
        }

 
        if (isdigit(curChar)) // если символ - число
        {
            state = stateMatrix[0][state];
            UNsym = false;
        }
        if (isalpha(curChar)) { // если символ - буква
            state = stateMatrix[1][state];
            UNsym = false;
        }
        if (curChar == ' ' || curChar == '\t' || curChar == '\n' || curChar == '\r' || curChar == '\0') // если встретился символ выхода
        {
            state = stateMatrix[2][state];
            UNsym = false;
        }
        
        if(UNsym) // всё остальное - мусор
        {
            state = stateMatrix[3][state];
        }
                
        if (state == AState::Final) // выход
        {
            if (lexem.word_fitting) // если слово подходит, записываем его
            {
                int length = cur_pos - first_pos; // вычисляем длину слова
                lexem.word = new char[length + 1]; // выделяем место под слово
                strncpy(&lexem.word[0], &text[0] + first_pos, length); // копируем слово из текста
                lexem.word[length] = '\0'; // ставим закрывающий символ
                if (length <= 6) { res.push_back(lexem); } // ограничение количества символов в слове	
                /*res.push_back(lexem);*/
                first_pos = cur_pos;
                lexem.word_fitting = false;
            }
            state = AState::Start;
        }
        else
        {
            if (state == AState::Fine ) // устраивающие нас состояния
            {
                lexem.word_fitting = true;
            }
            else
                if (state == AState::Error) // состояние ошибки
                {
                    lexem.word_fitting = false;
                }
        }
        cur_pos++;
        UNsym = true;
    }
}

int main()
{
    ifstream ifile("input.txt");

    if (ifile)
    {
        int size = 0;
        ifile.seekg(0, ios::end); // находим количество символов в файле
        size = ifile.tellg();
        ifile.seekg(0, ios::beg);
        if (size) {
            char* line = new char[size + 1]; // выделяем массив соответствующего размера
            ifile.getline(line, size + 1, '\0'); // считываем данные из файла в массив
            ifile.close(); // закрываем входной файл

            vector <Lex> result;
            LexAnalysis(line, size, result);
            ofstream ofile("output.txt");
            int j = result.size();
            for (int i = 0; i < j; i++)
            {
                cout << result[i] << ' ';
                ofile << result[i] << ' ';
            }
            result.clear();
            ofile.close();
        }
    }
}
