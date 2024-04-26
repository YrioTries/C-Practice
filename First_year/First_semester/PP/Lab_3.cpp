#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

void swap(int& arg1, int& arg2)
{
    int temp = arg1;
    arg1 = arg2;
    arg2 = temp;
};

int checkelements()
{
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << " Error of";
    }
    return a;
}

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
        /*double StartTime_ofSwap = clock();*/
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);
        /*double EndTime_ofSwap = clock();*/

        /*double StartTime_ofHeapify = clock();*/
        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
        /* double EndTime_ofHeapify = clock();*/
    }
}

int main()
{
    double FinalTime_ofHeapSort, FinalTime_ofSort, StartTime_ofSort, StartTime_ofHeapSort, EndTime_ofSort, EndTime_ofHeapSort;
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
        vector<int> Bector(size);

        int choice;
        cout << " Make a choice: " << endl;
        cout << " Enter '1', if you want to full the array automatically:" << endl;
        cout << " Enter '2', if you want to full the array by yourself:" << endl;
        cout << " Enter '3', if you want to full the array in small numers automatically:" << endl;
        cout << endl;
        cout << " ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:

            for (int i = 0; i < size; i++)
            {
                Gector[i] = rand();
                Bector[i] = Gector[i];
            }
            break;

        case 2:

            cout << endl;
            cout << " Full the Array by yourself:" << endl;
            cout << endl;

            for (int i = 0; i < size; i++)
            {
                /*int elements;*/
                cout << " ";
                /*elements = checkelements();*/
                Gector[i] = checkelements();
                Bector[i] = Gector[i];
            }
            break;

        case 3:
            for (int i = 0; i < size; i++)
            {
                Gector[i] = rand() % 3 + 1;
                Bector[i] = Gector[i];
            }
            break;

        default:
            cout << endl;
            cout << " Error! You entered incorrect number..." << endl;
            break;
        }

        if (size <= 15)
        {
            cout << endl;
            cout << " Array before sorting: " << endl;
            cout << endl;

            Print(Gector, size);
            cout << endl;
        }
        else
        {
            cout << " Array is Full, fiveteen nubers of array: " << endl;
            cout << endl;


            Print(Gector, bize);
            cout << endl;
        }

        StartTime_ofHeapSort = clock();
        HeapSort(Gector, size);
        EndTime_ofHeapSort = clock();

        StartTime_ofSort = clock();
        sort(Bector.begin(), Bector.end());
        EndTime_ofSort = clock();

        if (size <= 15)
        {
            cout << endl;
            cout << " Sorted array is: " << endl;
            cout << endl;

            Print(Gector, size);
            cout << endl;
        }
        else
        {
            cout << endl;
            cout << " Sorted array is: " << endl;
            cout << endl;

            Print(Gector, bize);
            cout << endl;
        }

        FinalTime_ofHeapSort = (double)(EndTime_ofHeapSort - StartTime_ofHeapSort) / CLOCKS_PER_SEC;
        FinalTime_ofSort = (double)(EndTime_ofHeapSort  - StartTime_ofSort) / CLOCKS_PER_SEC;

        cout << " Time of 'HeapSort' function: " << FinalTime_ofHeapSort << endl;
        cout << " Time of 'Sort' function: " << FinalTime_ofSort << endl;

        if (FinalTime_ofHeapSort < 1 || FinalTime_ofSort < 1) 
        {
            cout << " Sorts are incvivalence" << endl;
        }
        else 
        {
            if (FinalTime_ofHeapSort > FinalTime_ofSort) 
            {
                cout << " Lib sort faster in " << FinalTime_ofHeapSort / FinalTime_ofSort << " times" << endl;
            }
            else cout << " HeapSort faster in " << FinalTime_ofSort / FinalTime_ofHeapSort << " times" << endl;
        }

        cout << endl;
        cout << " Do you want to continue (Y/N): " << endl;
        cout << " ";

        cin >> w;
        cout << endl;

    } while (w == 'y' || w == 'Y');
}
