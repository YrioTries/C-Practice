#include<WinSock2.h>
#include<iostream>
#include<Windows.h>
#include<math.h>
#pragma warning(disable:4996)
#pragma comment(lib, "ws2_32.lib")
using namespace std;


void getWords(SOCKET Connection)
{
	char buffer[1024] = { 0 };
	cout << "Waiting for words...\n" << endl;

	while (recv(Connection, (char*)&buffer, 1024, NULL) > 0) {
		cout << "[RECEIVE]: " << "[" << buffer << "]" << endl;
		memset(buffer, 0, sizeof(buffer));
	}
}

void initWSA()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error" << endl;
		exit(1);
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	initWSA();
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	// проверяем на подключение к серверу
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr))) {
		cout << "Failure in connection to server!" << '\n';
		return 1;
	}
	else {
		cout << "Connected!" << endl;
		getWords(Connection);
		closesocket(Connection);
		WSACleanup();
	}
}
