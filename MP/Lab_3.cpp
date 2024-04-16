#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void swap(int& arg1, int& arg2)
{
    int temp = arg1;
    arg1 = arg2;
    arg2 = temp;
};

void Print(vector<int>& arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << " ";
        cout << arr[i] << " ";
        cout << "\n";
    }
}

void heapify(vector<int>& arr, int n, int i)
{
    int largest = i;
    // Инициализируем наибольший элемент как корень
    int l = 2 * i + 1; // левый = 2*i + 1
    int r = 2 * i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Если самый большой элемент не корень 
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, n, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void HeapSort(vector<int>& arr, int n)
{
    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--)
    {

        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

int main()
{
    int bize = 15;
    char w;
    do
    {
        int size{};

        cout << " Enter the size of an array in range of 1 to 15: " << endl;
        cout << " ";
        cin >> size;
        cout << endl;

        vector<int> Gector(size);

        for (int i = 0; i < size; i++)
        {
            Gector[i] = rand();
        }

        if (size <= 15)
        {
            cout << " Array before sorting: " << endl;
            cout << endl;

            Print(Gector, size);
            cout << endl;
        }
        else
        {
            cout << " Array is Full, fiveteen nubers od array: " << endl;
            cout << endl;


            Print(Gector, bize);
            cout << endl;
        }

        HeapSort(Gector, size);

        if (size <= 15)
        {
            cout << endl;
            cout << "Sorted array is: " << endl;
            cout << endl;

            Print(Gector, size);
            cout << endl;
        }
        else
        {
            cout << endl;
            cout << "Sorted array is: " << endl;
            cout << endl;

            Print(Gector, bize);
            cout << endl;
        }

        cout << "" << endl;
        cout << " Do you want to continue (Y/N): " << endl;
        cout << " ";

        cin >> w;
        cout << endl;

    } while (w == 'y' || w == 'Y');
}
