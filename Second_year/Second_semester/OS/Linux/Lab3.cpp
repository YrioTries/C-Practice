#include <iostream>
#include <cmath>
#include <unistd.h>
#include <cstring>
using namespace std;

int pipe_in[2];
int pipe_out[2];

double read_int(const string& msg)
{
    double result;
    bool flag = true;
    while (flag)
    {
        cout << msg;
        cin >> result;
        if ((cin.fail() || (cin.peek() != '\n'))) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input error\n";
        }
        else {
            flag = false;
        }
    }
    return result;
}

void client() {
    int rows, cols, num;
    rows = read_int("Enter the number of rows: ");
    cols = read_int("Enter the number of cols: ");

    write(pipe_in[1], &rows, sizeof(int));
    write(pipe_in[1], &cols, sizeof(int));

    // Enter matrix values
    cout << "\nEnter Matrix values:" << endl;
    for (int i = 0; i < rows; i++) {
        cout << endl;
        for (int j = 0; j < cols; j++) {
            cout << "Element[" << i + 1 << "][" << j + 1 << "]: " << endl;
            num = read_int("");
            write(pipe_in[1], &num, sizeof(int));
        }
    }
    
    cout << endl;
    
    for (int i = 0; i < cols; i++) { // Переносим информацию из масива в матрицу	
        cout << endl;
        for (int j = 0; j < rows; j++) {
            read(pipe_out[0], &num, sizeof(int));
            cout << "|   ";
            cout << num << " ";

            if (num >= 0) {
                cout << " ";
            }
            if (abs(num) < 10) {
                cout << " ";
            }
        }
        cout << "|";
    }
    cout<<"\n" << endl;
}

void server() {
    int rows, cols, num;

    read(pipe_in[0], &rows, sizeof(int));
    read(pipe_in[0], &cols, sizeof(int));

    int** matrix = new int* [rows]; // Создание двумерного массива для исходной матрицы
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++) { // Переносим информацию из масива в матрицу	
        for (int j = 0; j < cols; j++) {
            read(pipe_in[0], &num, sizeof(int));
            matrix[i][j] = num; 
        }
    }

    cout << endl;
    cout << "Your matrix:" << endl;

    for (int i = 0; i < rows; i++) { // Переносим информацию из масива в матрицу	
        cout << endl;
        for (int j = 0; j < cols; j++) {

            cout << "|   ";
            cout << matrix[i][j] << " ";

            if (matrix[i][j] >= 0) {
                cout << " ";
            }
            if (abs(matrix[i][j]) < 10) {
                cout << " ";
            }
        }
        cout << "|";
    }

    // Calculate matrix trans
    cout << "\n" << endl;
    cout << "Transposed matrix:" << endl;

    for (int i = 0; i < cols; i++) {
        cout << endl;
        for (int j = 0; j < rows; j++) {
            num = matrix[j][i]; // Транспонируем матрицу, записываем в массив
            write(pipe_out[1], &num, sizeof(int));

            cout << "|   ";
            cout << num << " ";

            if (num >= 0) {
                cout << " ";
            }

            if (abs(num) < 10) {
                cout << " ";
            }
        }
        cout << "|";
    }
    cout << "\n" << endl;
    cout << "Transferred transposed matrix:\n" << endl;

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i]; // Освобождение памяти
    }
    delete[] matrix; // Освобождение памяти
}

int main(int argc, char* argv[]) {
    if (argc == 2 && !strcmp(argv[1], "--help")) {
        cout << "To run matrix addition, run the program without keys.\n";
        return 0;
    }
    else if (argc != 1) {
        cout << "Run the program with the --help switch to get help.\n";
    }
    else {
        pipe(pipe_in);
        pipe(pipe_out);
        pid_t pid = fork();

        if (pid == 0) {
            // Child process: server
            server();
            close(pipe_in[1]);
            close(pipe_out[0]);
            
        }
        else {
            // Parent process: client
            client();
            close(pipe_in[0]);
            close(pipe_out[1]);
            
        }
    }

    return 0;
}
