
#define URL				"www.facebook.com"
#include<WS2tcpip.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
void mfailed(string msg) {
	printf("%s", msg.c_str());
	system("pause");
	exit(0);
}

int main() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		mfailed("WSAStartup failed.\n");

	//setting host data
	struct addrinfo hint;
	ZeroMemory(&hint, sizeof(hint));
	hint.ai_family = AF_INET;
	hint.ai_protocol = IPPROTO_TCP;
	hint.ai_socktype = SOCK_STREAM;
	struct addrinfo *targetAddressInfo = NULL;
	DWORD getAddressRes = getaddrinfo(URL, "80", &hint, &targetAddressInfo);
	if (getAddressRes != 0 || targetAddressInfo == NULL)
		mfailed("Failed to set target Address.");

	//setting socket
	SOCKET webSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (webSocket == INVALID_SOCKET)
		mfailed("Socket Failed!");

	for (addrinfo *i = targetAddressInfo; i != NULL; i = i->ai_next) {
		sockaddr_in *address = (sockaddr_in*) i->ai_addr;
			cout << (int)((*address).sin_addr.S_un.S_un_b.s_b1) << '.'
			<< (int)(*address).sin_addr.S_un.S_un_b.s_b2 << '.'
			<< (int)(*address).sin_addr.S_un.S_un_b.s_b3 << '.'
			<< (int)(*address).sin_addr.S_un.S_un_b.s_b4 << "::"
			<< (int)(*address).sin_port << endl;
	}
	//setting socket address
	SOCKADDR_IN addressData;
	addressData.sin_port = htons(80);
	addressData.sin_family = AF_INET;
	addressData.sin_addr = ((struct sockaddr_in*)targetAddressInfo->ai_addr)->sin_addr;

	//free
	freeaddrinfo(targetAddressInfo);

	//connect
	cout << "Connecting......\n";
	if (connect(webSocket, (SOCKADDR*)&addressData, sizeof(addressData)) != 0)
		mfailed("Could not Connect!");
	cout << "Connected!\n";

	char header[] =
		"GET /v2.5/100001223883789 HTTP/1.1\r\n"
		"Host: graph.facebook.com\r\n"
		//"GET /?gfe_rd=cr&ei=duW6VsjtCOmT9QWk7oLYBg HTTP/1.1\r\n"
		"Connection: keep-alive\r\n"
		//"Set-Cookie: NID=76=C3ZkRsRu2D_0kd76pznU9LSnuZNi8N4ekiKBcRFh_QLuA9ErCpVEIG6kZHDkMC25TFttDInpjc0heJKMYU22z6lRWy3s4aIzsVAF1NGFmjHNfWNP_d - sfW84VaXhTQgk6 - fnMfgmHLc;expires = Thu, 11 - Aug - 2016 07:27 : 19 GMT; path = / ; domain = .google.com; HttpOnly\r\n"
		"\r\n";

	//Send Request~
	int sentBytes = send(webSocket, header, strlen(header), 0);
	if (sentBytes < strlen(header) || sentBytes == SOCKET_ERROR)
		mfailed("send failed!");

	//Response
	constexpr int iLong =  10000;
	char strData[iLong];
	ZeroMemory(strData, sizeof(strData));
	while (recv(webSocket, strData, iLong, 0) > 0) {
		int i = 0;
		while (strData[i] > 0) {
			cout << strData[i];
			i++;
		}
	}
	closesocket(webSocket);
	WSACleanup();
	system("pause");
	return 0;
}