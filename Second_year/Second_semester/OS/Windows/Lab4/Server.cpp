#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <winsock2.h>
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector <SOCKET> Connections;
int connectionsCounter = 0;
const char* CD_COMMAND = "cd D:\\My project diskD\\Client_OS4\\x64\\Debug";
const char* START_COMMAND = "start D:\\My project diskD\\Client_OS4\\x64\\Debug\\Client_OS4.exe";

void initLibrary()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error loading WSA" << endl;
		exit(1);
	}
}

void startClientFromTerminal()
{
	// проверка на случай непредвиденных обстоятельств
	int command_not_execute = system(CD_COMMAND); // передаёт процессору команду в строке
	if (command_not_execute)
	{
		cout << "Failed to start command" << '\n';
		exit(1);
	}
	system(START_COMMAND);
}

void giveWordsToClient(SOCKET newConnection, int amount_of_clients, int i) {
	string num = to_string(i + 1);
	string word = "Hello from Client N" + num;
	
	int count = 0;

	cout << "[SEND] " << "[" << word << "]" << " [ TO " << newConnection << "]" << endl;
	int result = send(newConnection, word.c_str(), word.length(), NULL);
}

int getSocketNumber()
{
	int clientNumber;
	int leftBorder = 3;
	int rightBorder = 10;
	cout << "Input number of Clients (n): ";
	while (!(cin >> clientNumber) || (cin.peek() != '\n') || (clientNumber < leftBorder) || (clientNumber > rightBorder)) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error : Input correct number of Clients..." << '\n';
	}
	return clientNumber;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	initLibrary();

	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
	int sizeofaddr = sizeof(addr);

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;

	STARTUPINFO si;
	PROCESS_INFORMATION pi; // хранит дискрипторы и идентификаторы для нового процессы

	ZeroMemory(&si, sizeof(si)); // обнуляет переменную по ссылке
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	int n = getSocketNumber();

	for (int i = 0; i < n; ++i) {
		if (!CreateProcess(L"D:\\My project diskD\\Client_OS4\\x64\\Debug\\Client_OS4.exe",
			NULL,
			NULL,
			NULL,
			FALSE,
			CREATE_NEW_CONSOLE,
			NULL,
			NULL,
			&si,
			&pi)) {
			cout << "Error! Process creation failed! Error code: " << GetLastError() << ".\n";
			closesocket(sListen);
			WSACleanup();
		}
	}

	for (int i = 0; i < n; ++i)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr); // возвращает сокет дискриптор для ощения сервера и клиента
		Connections.push_back(newConnection);
		if (newConnection == 0)
		{
			cout << "Socket Connection Error" << endl;
		}
		else
		{
			cout << "Clients connected Successfully!" << endl;
			giveWordsToClient(newConnection, n, i);
		}
		++connectionsCounter;
	}

	// Check for client disconnection
	char buffer[4096];
	int bytesReceived = 0;

	while (true) {

		for (int i = 0; i < n; i++) {
			bytesReceived = recv(Connections[i], buffer, sizeof(buffer), 0);
			
			if (bytesReceived == SOCKET_ERROR) {
				cout << "Client N"<< i + 1 <<" disconnected." << endl;
			}
		}

		if (bytesReceived == SOCKET_ERROR) {
			cerr << "Receive error." << endl;
			break;
		}
		
	}

	for (int i = 0; i < n; i++) {
		closesocket(Connections[i]);
	}

	WSACleanup();

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}
