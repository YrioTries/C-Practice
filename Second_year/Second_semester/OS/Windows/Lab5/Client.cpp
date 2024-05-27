#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <thread>
#include<string>
#include<winsock2.h>
#pragma warning(disable: 4996) //для inet_addr

using namespace std;

void function(SOCKET Connection) {
    while (true) {
        char buffer[1024];
        int bytesReceived = recv(Connection, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            if (strcmp(buffer, "\n Goodbye youser!") == 0) {
                return;
            }
            else {
                cout << buffer;
            }
        }
        else return;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Пивет, я представляю клиенстскую программу" << endl 
        << "Напишите 'готов' для начала работы с сервером" << endl 
        << "Потом введите ключ-слово (getData/changeData) и параметры через пробел)" << endl;
    //загружаем WSAStartup
    WSAData wsaData; //создаем структуру для загрузки
    WORD DLLVersion = MAKEWORD(2, 1);

    if (WSAStartup(DLLVersion, &wsaData) != 0) { //проверка на подключение библиотеки

        cout << "Error" << endl;
        exit(1);
    }

    //Заполняем информацию об адресе сокета
    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //адрес
    addr.sin_port = htons(1111); //порт
    addr.sin_family = AF_INET; //семейство протоколов
    //сокет для прослушивания порта
    SOCKET Connection = socket(AF_INET, SOCK_STREAM, 0);//возвращает целочисленное значение, идентифицирующее созданный сокет аналогично дескриптору файла

    //проверка на подключение к серверу

    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr))) {
        string code_error = to_string(WSAGetLastError());
        string error_msg = "Установить соединение с сервером не удалось! Код ошибки: ";
        string msg_of_error = error_msg + code_error;
        cout << msg_of_error;
        closesocket(Connection); // Закрыть сокет
        WSACleanup(); // Очистить Winsock
        return 1;
    }

    thread t(function, Connection);
    string start;
    cin >> start;
    HANDLE hMutex = OpenMutexW(SYNCHRONIZE, FALSE, L"MyMutex");


    WaitForSingleObject(hMutex, INFINITE);
    string message;
    while (message != "finish") {

        getline(cin, message);
        // Отправка сообщения

        int bytesSent = send(Connection, message.c_str(), (int)strlen(message.c_str()), 0);
        if (bytesSent == -1) {
            cerr << "Error sending data\n";
        }
    }
    ReleaseMutex(hMutex);
    t.join();

    if (closesocket(Connection) == SOCKET_ERROR)
        cerr << "Failed to terminate connection.\n Error code: " << WSAGetLastError();

    WSACleanup();

    return 0;
}
