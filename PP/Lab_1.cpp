#include<iostream>
using namespace std;

int main()
{
    int v;
    bool flag;

    do {

        int size1, size2;
        do {
            do {
                cout << " Enter size of the array: " << endl;
                cout << " ";
                cin >> size1;
                if (size1 < 2) 
                {
                    cout << " Error. You enteredvan an invailid value, check your input. " << endl;
                    cout << " Array length can not be negative " << endl;
                    cout << " " << endl;
                    cout << " Try again: " << endl;
                    cout << " " << endl;
                }
            } while (size1 < 2);
            do {
                cout << " Enter size of the subarray: " << endl;
                cout << " ";
                cin >> size2;
                if (size2 < 2) 
                {
                    cout << " " << endl;
                    cout << " Error. You enteredvan an invailid value, check your input. " << endl;
                    cout << " Array length can not be negative. " << endl;
                    cout << " " << endl;
                    cout << " Try again: " << endl;
                    cout << " " << endl;
                }
            } while (size2 < 2);
            if (size1 <= size2) 
            {
                cout << " " << endl;
                cout << " Error. You enteredvan an invailid value, check your input. " << endl;
                cout << " The length of a subarray cannot be longer than the array " << endl;
                cout << " " << endl;
                cout << " Try again: " << endl;
                cout << " " << endl;
            }
        } while (size1 <= size2);

        cout << " " << endl;
        cout << " Full the first array: " << endl;
        cout << " " << endl;

        string* arr1 = new string[size1];
        for (int i = 0; i < size1; i++) 
        {
            cout << " ";
            cin >> arr1[i];
        }
        
        cout << " " << endl;
        cout << " Full the second array: " << endl;
        cout << " " << endl;

        string* arr2 = new string[size2];
        for (int k = 0; k < size2; k++) 
        {
            cout << " ";
            cin >> arr2[k];
        }

        int k = 0;
        int size;
        size = size1 - size2;
        flag = true;
        for (int i = 0;i < size + 1;i++) {
            for (int j = 0; j < size2;j++) {
                if (arr1[i + j] != arr2[j])
                    flag = false;

            }
            if (flag)

                k++;
            flag = true;
        }

        cout << " " << endl;
        cout << " The number of occurrences of a subarray in array = " << " " << k << endl;
        cout << " If you want to continue working with the program, press '1' : " << endl;
        cout << " ";
        cin >> v;

        delete[] arr1;
        delete[] arr2;

    } while (v == 1);
}
