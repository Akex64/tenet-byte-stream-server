#include "server.h"

void server::set_thread(void* thread) {
	void* (*cThread)() = reinterpret_cast<decltype(cThread)>(thread);
	this->clientThread = cThread;
}

void server::initialize(int port) {
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	addr.sin_port = htons(port);  
	addr.sin_family = AF_INET; 

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	this->connectionsindex = 0;

	for (int i = 0; i < 250; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen);
		if (!(newConnection == 0)) {
			this->connections[i] = newConnection;
			this->connectionsindex += 1;
			printf("[+] New Client %p\n", (void*)newConnection);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)this->clientThread, (LPVOID)(i), 0, 0);
		}
	}
}