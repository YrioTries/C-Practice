#include <iostream>
#include <fstream>
using namespace std;

class NodeFR {

public:
    int N_numerator; // Числитель
    int N_denominator; // Знаменатель
    NodeFR* n_next, * n_prev; // Указатели на следующий и прошлый элемент


    void simplify() { // Метод сокращения дроби
        if (N_denominator < 0) {
            N_numerator *= -1;
            N_denominator *= -1;
        }
        if (abs(N_numerator) < 2) return;
        int gcd = getGCD(abs(N_numerator), N_denominator);
        N_numerator /= gcd;
        N_denominator /= gcd;
    }

    // Конструкторы
    NodeFR(int nominator, int denominator) : N_numerator(nominator), N_denominator(denominator) {
        if (this->N_denominator == 0) throw logic_error("Division by zero.");
        simplify();
    }

    NodeFR() : N_numerator(0), N_denominator(1) {}
    NodeFR(const NodeFR& other) : N_numerator(other.getNominator()), N_denominator(other.getDenominator()) {} // Конструктор копирования
    NodeFR(int value) : N_numerator(value), N_denominator(1) {}

    ~NodeFR() {} // Деструктор

    // Геттеры
    int getNominator() const { return N_numerator; }
    int getDenominator() const { return N_denominator; }

    // Медод десятич. представления
    double dfraction() { double num = N_numerator, den = N_denominator; return (num / den); }

    // Сравниватель
    double compareTo(const NodeFR& other) const {
        return N_numerator * other.N_denominator - N_denominator * other.N_numerator;
    }

    // Поиск наим. общего множителя
    static int getGCD(int a, int b) {
        while (a != b)
            if (a > b) a -= b; else b -= a;
        return a;
    }

    //  Дружим вывод и ввод в файл с классом
    friend ostream& operator << (ostream& ofs, const NodeFR& fraction) { // Вывод
        ofs << fraction.getNominator() << '/' << fraction.getDenominator();
        return ofs;
    }

    friend ifstream& operator >> (ifstream& ifs, NodeFR& fraction) { // Ввод
        ifs >> fraction.N_numerator >> fraction.N_denominator;
        return ifs;
    }

    // И арифм. операции тоже
    friend NodeFR operator-(const NodeFR& a) { return NodeFR(-a.N_numerator, a.N_denominator); }

    friend NodeFR operator+(const NodeFR& a, const NodeFR& b) {
        int commonDenominator = a.N_denominator * b.N_denominator;
        int commonNominator = a.N_numerator * b.N_denominator + b.N_numerator * a.N_denominator;
        return NodeFR(commonNominator, commonDenominator);
    }

    friend NodeFR operator-(const NodeFR& a, const NodeFR& b) { return a + -b; }
    friend NodeFR operator*(const NodeFR& a, const NodeFR& b) { return NodeFR(a.N_numerator * b.N_numerator, a.N_denominator * b.N_denominator); }
    friend NodeFR operator/(const NodeFR& a, const NodeFR& b) { return NodeFR(a.N_numerator * b.N_denominator, a.N_denominator * b.N_numerator); }
};

// Подкючение булевых операторов
bool operator==(const NodeFR& a, const NodeFR& b) {
    return a.compareTo(b) == 0;
}

bool operator!=(const NodeFR& a, const NodeFR& b) {
    return !(a.compareTo(b) == 0);
}

bool operator<(const NodeFR& a, const NodeFR& b) {
    return a.compareTo(b) < 0;
}

bool operator>(const NodeFR& a, const NodeFR& b) {
    return a.compareTo(b) > 0;
}

bool operator<=(const NodeFR& a, const NodeFR& b) {
    return a.compareTo(b) <= 0;
}

bool operator>=(const NodeFR& a, const NodeFR& b) {
    return a.compareTo(b) >= 0;
}

class List_for_us
{
    int i_size;

public:
    NodeFR* NodeFRHead, * NodeFRTail; // Голова и хвост

    List_for_us(); // Конструктор
    List_for_us(const List_for_us&); // Конструктор копирования
    ~List_for_us(); // Деструктор

    int GetSize_for_us() { return i_size; } // Возвращает размер
    void clearListPls() { while (i_size != 0) { DeleteNode(1); } } // Метод удаление списка
    void DeleteNode(int y = 0); // Удаление элемента если не указывается параметр, он запрашивается
    void L_push_back(int n, int d); // Добавление в конец списка
};

List_for_us::List_for_us() // Конструкторы
{
    i_size = 0;
    NodeFRHead = NULL;
    NodeFRTail = NULL;
}

List_for_us::List_for_us(const List_for_us& Listok)
{
    NodeFRHead = NULL;
    NodeFRTail = NULL;
    i_size = 0;

    NodeFR* needNode = Listok.NodeFRHead;

    while (needNode != 0)
    {
        L_push_back(needNode->N_numerator, needNode->N_denominator);
        needNode = needNode->n_next;
    }
}

List_for_us::~List_for_us() // Деструктор
{
    clearListPls();
}

void List_for_us::L_push_back(int n, int d)
{
    NodeFR* needNode = new NodeFR;
    needNode->N_numerator = n;
    needNode->N_denominator = d;
    needNode->n_next = 0;
    needNode->n_prev = NodeFRTail;

    if (NodeFRTail != 0) {
        NodeFRTail->n_next = needNode;
    }

    if (i_size == 0) {
        NodeFRHead = NodeFRTail = needNode;
    }

    else {
        NodeFRTail = needNode;
    }

    i_size++; // Увеличиваем переменную размера списка
}

void List_for_us::DeleteNode(int var) // Удаление узла
{
    if (var < 1 || var > i_size)
    {
        cout << "Incorrect position" << endl;
        return;
    }

    if (var == 0)
    {
        cout << "Input position: ";
        cin >> var;
    }

    int w = 1;

    NodeFR* D = NodeFRHead;

    while (w < var)
    {
        D = D->n_next;
        w++;
    }

    NodeFR* prevD = D->n_prev;
    NodeFR* AfterDel = D->n_next;

    if (prevD != 0 && i_size != 1) {
        prevD->n_next = AfterDel;
    }

    if (AfterDel != 0 && i_size != 1) {
        AfterDel->n_prev = prevD;
    }

    if (var == 1) {
        NodeFRHead = AfterDel;
    }

    if (var == i_size) {
        NodeFRTail = prevD;
    }

    delete D;

    i_size--; // Уменьшение значения размера списка
}

void SortSelection(List_for_us* Listok) // Сортировка выбором
{
    NodeFR* i, * j, * curMin;
    for (i = Listok->NodeFRHead; i != NULL; i = i->n_next)
    {
        curMin = i;
        for (j = i->n_next; j != NULL; j = j->n_next)
        {
            if (*j < *curMin) // Выбор минимального
            {
                curMin = j;
            }
        }
        if (curMin != i)
        {
            // Перестановка элементоа
            int n = curMin->N_numerator;
            int d = curMin->N_denominator;
            curMin->N_numerator = i->N_numerator;
            curMin->N_denominator = i->N_denominator;
            i->N_numerator = n;
            i->N_denominator = d;
        }
    }
}

void prov_of_our_List(List_for_us* Listok) // Функция проверки корректности сортировки 
{
    NodeFR* cur;
    bool error = false;
    for (cur = Listok->NodeFRHead->n_next; cur != NULL; cur = cur->n_next)
    {
        if (*cur->n_prev > *cur) {
            error = true;
        }
    }

    if (error) {
        cout << "Error of sorting!!!" << endl;
    }
    else {
        cout << "Sorting was done correctly!! \n"  << endl;
        cout << "Sorted list items: " << endl;

    }
}

void Print_Listok(NodeFR* head, int i_size) // Функция для вывода списка
{
    ofstream fout_output("output.txt");
    fout_output << i_size << " ";
    NodeFR* n_curr = head;

    while (n_curr != nullptr)
    {
        cout << *n_curr << " ";
        n_curr = n_curr->n_next;
    }
    fout_output.close();
}

int main()
{
    List_for_us Listok; // Создание списка
    ifstream fin_input("input.txt");
    int Num, i = 0;

    fin_input >> Num; // Флаг для определения числа элементов списка

    while (i < Num)
    {
        Listok.L_push_back(rand() % 1000 + 1, rand() % 1000 + 1); // Добавление элементов в список
        i++;
    }
    fin_input.close(); // Закрытие файла

    int i_size2 = Listok.GetSize_for_us();
    NodeFR* head = Listok.NodeFRHead; // Получение головы списка

    SortSelection(&Listok); // Сортируем список
    prov_of_our_List(&Listok); // Проверяем корректность сортировки
    Print_Listok(head, i_size2); // Выводим необходимую информацию

    return 0;
}
