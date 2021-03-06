#include "stdafx.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996) 

using namespace std;

int main() {
	//------------------------------------------------------------

	HANDLE hIcmpFile;															//объявление необходимых переменных
	unsigned long ipaddr = INADDR_NONE;
	DWORD dwRetVal = 0;
	char SendData[32] = "Data Buffer";
	LPVOID ReplyBuffer = NULL;
	DWORD ReplySize = 0;
	
	//------------------------------------------------------------

	ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
	ReplyBuffer = (VOID*)malloc(ReplySize);

	const char* pointerToAddres;													//указатель на текущий ip-шник

	/*for (int i = 0; i <= 255; i++) {

		for (int j = 0; j <= 255; j++) {*/

	while (true) {
		//------------------------------------------------------------
		/*char buffer1[3];
		char buffer2[3];*/

		char layout[16] = "192.168.";

		/*strcat(layout, itoa(i, buffer1, 10));								//собираем ip-шник
		strcat(layout, ".");
		strcat(layout, itoa(j, buffer2, 10));

		*/

		cout << "Adress: " << endl;

		cin >> layout;

		pointerToAddres = layout;

		//----------------------------------------------------------------

		cout << pointerToAddres << "\n";

		ipaddr = inet_addr(pointerToAddres);				//переводим адрес в нужный формат

		hIcmpFile = IcmpCreateFile();						//открываем соединение

		dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData), NULL, ReplyBuffer, ReplySize, 1000);  //посылаем запрос

		PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;  //записываем ответ
		struct in_addr ReplyAddr;
		ReplyAddr.S_un.S_addr = pEchoReply->Address;

		printf("Addres: %s ", inet_ntoa(ReplyAddr));						//выводим
		printf("Ping = %ld milliseconds\n", pEchoReply->RoundTripTime);

		//------------------------------------------------------------
		IcmpCloseHandle(hIcmpFile);							//закрываем конект
	}
			
		/*}
	}*/

	system("pause");
	return 0;
}