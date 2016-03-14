/*
#include<WS2tcpip.h>
#include<WinInet.h>
//#include <windows.h> 
#include<process.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
struct myrettype {
	SOCKET AcceptSocket;
	sockaddr_in addrclient;
};

unsigned __stdcall Connection1(void* in) {
	cout << "someone link in" << endl;
	return 0;
}

int Server() {
	// Initialize Winsock
	SOCKET m_socket = INVALID_SOCKET;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
		printf("Socket初始化失敗。\n");
		return -1;
	}

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		printf("連線失敗。錯誤碼：%ld\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = htonl(INADDR_ANY);
	service.sin_port = htons(80);

	if (bind(m_socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		printf("Port開啟失敗\n", WSAGetLastError());
		closesocket(m_socket);
		return -1;
	}

	if (listen(m_socket, 50) == SOCKET_ERROR)
		printf("監聽失敗。錯誤碼：%ld.\n", WSAGetLastError());

	SOCKET AcceptSocket;
	printf("等待使用者連線...\n");

	unsigned ret;

	do {
		sockaddr_in addrclient;
		int addrclientlen = sizeof(addrclient);
		AcceptSocket = accept(m_socket, (sockaddr FAR *) &addrclient, &addrclientlen);
		myrettype *tmp;
		tmp = new myrettype;
		tmp->AcceptSocket = AcceptSocket;
		tmp->addrclient = addrclient;


		if (AcceptSocket != SOCKET_ERROR)
			_beginthreadex(0, 0, Connection1, tmp, 0, &ret);

	} while (AcceptSocket != SOCKET_ERROR);


	WSACleanup();
	return 0;
}*/