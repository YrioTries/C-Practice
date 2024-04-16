#include <iostream>
#include <fstream>
using namespace std;

class Node // Узел списка
{
public:
    int i_data;
    Node* n_next, * n_prev; // Указатели на следующий и прошлый элемент
};

class List_for_us
{
    int i_size;

public:
    Node* NodeHead, * NodeTail; // Голова и хвост

    List_for_us(); // Конструктор
    List_for_us(const List_for_us&); // Конструктор копирования
    ~List_for_us(); // Деструктор

    int GetSize() { return i_size; } // Возвращает размер
    void clear(); // Метод удаление списка
    void DeleteNode(int y = 0); // Удаление элемента если не указывается параметр, он запрашивается
    void push_back(int n); // Добавление в конец списка
    void push_front(int n); // Добавление в начало списка
};

List_for_us::List_for_us()
{
    i_size = 0;
    NodeHead = NULL;
    NodeTail = NULL;
}

List_for_us::List_for_us(const List_for_us& Listok)
{
    NodeHead = NULL;
    NodeTail = NULL;
    i_size = 0;

    Node* need = Listok.NodeHead;

    while (need != 0)
    {
        push_back(need->i_data);
        need = need->n_next;
    }
}

List_for_us::~List_for_us()
{
    clear();
}

void List_for_us::push_front(int n)
{

    Node* need = new Node;

    need->n_prev = 0;
    need->i_data = n;
    need->n_next = NodeHead;

    if (NodeHead != 0) {
        NodeHead->n_prev = need;
    }

    if (i_size == 0) {
        NodeHead = NodeTail = need;
    }
    else {
        NodeHead = need;
    }

    i_size++;
}

void List_for_us::push_back(int n)
{
    Node* need = new Node;
    need->i_data = n;
    need->n_next = 0;  
    need->n_prev = NodeTail;

    if (NodeTail != 0) {
        NodeTail->n_next = need;
    }

    if (i_size == 0) {
        NodeHead = NodeTail = need;
    }

    else {
        NodeTail = need;
    }

    i_size++;
}

void List_for_us::DeleteNode(int var)
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

    Node* D = NodeHead;

    while (w < var)
    {
        D = D->n_next;
        w++;
    }

    Node* prevD = D->n_prev;
    Node* AfterDel = D->n_next;

    if (prevD != 0 && i_size != 1) {
        prevD->n_next = AfterDel;
    }

    if (AfterDel != 0 && i_size != 1) {
        AfterDel->n_prev = prevD;
    }

    if (var == 1) {
        NodeHead = AfterDel;
    }

    if (var == i_size) {
        NodeTail = prevD;
    }

    delete D;

    i_size--;
}

void List_for_us::clear()
{
    while (i_size != 0) { DeleteNode(1); }
}

void SortSelection(List_for_us* Listok) // Сортировка выбором
{
    Node* i, * j, * curMin;
    for (i = Listok->NodeHead; i != NULL; i = i->n_next)
    {
        curMin = i;
        for (j = i->n_next; j != NULL; j = j->n_next)
        {
            if (j->i_data < curMin->i_data) // Выбор минимального
            {
                curMin = j;
            }
        }
        if (curMin != i)
        {
            int need = curMin->i_data;
            curMin->i_data = i->i_data;
            i->i_data = need;
        }
    }
}

void Print(Node* head, int size) // Функция для вывода списка
{
    ofstream fout_output("output.txt");
    fout_output << size << " ";
    cout << size << " ";
    Node* n_curr = head;

    while (n_curr != nullptr)
    {
        fout_output << n_curr->i_data << " ";
        cout << n_curr->i_data << " ";
        n_curr = n_curr->n_next;
    }
    fout_output.close();
}

int main()
{
    List_for_us Listok;
    bool flag_sorty;
    int need;

    ifstream fin_input("input.txt");
    
    fin_input >> flag_sorty; //флаг для определения сортировки
   
    while (fin_input >> need)
    {
        Listok.push_back(need); //добавление элементов в список
    }
    fin_input.close();

    int i_size2 = Listok.GetSize();
    Node* head = Listok.NodeHead; // Получение головы списка

    if (flag_sorty == 0) // Выбор сортировки
    {
        SortSelection(&Listok);
        Print(head, i_size2);
    }
    else
    {
        Print(head, i_size2);
    }

    return 0;
}
