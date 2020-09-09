#include "server.h"
#include "util.h"

server* m_server;

unsigned char bytes[6] = { 0x00,0x52,0x44,0x43 }; // enter bytes of a valid application

void* ClientThread(int conindex) {
	util* util{ 0 };
	try
	{
		char action[512];
		recv(m_server->connections[conindex], action, sizeof(action), NULL);


		auto args = util->split(action, " ");

		if (args[0] == "stream")
		{
			Auth auth("YOURPRODUCTKEY", {});
			Response res;
			auth.ProcessKey(res, args[1]);

			if (res.Error.m_succeed) {
				for (auto byte : bytes) {
					send(m_server->connections[conindex], std::to_string(byte).c_str(), sizeof(std::to_string(byte).c_str()), NULL);
				}
				send(m_server->connections[conindex], "Finish", sizeof("Finish"), NULL);
				printf("[+] Streamed bytes to %p\n", (void*)m_server->connections[conindex]);
			}
			else {
				send(m_server->connections[conindex], "Failed", sizeof("Failed"), NULL);
				Sleep(60000);
			}
		}
	}
	catch (...)
	{

	}

	closesocket(m_server->connections[conindex]);
	m_server->connectionsindex -= 1;
	ExitThread(1);
}

int main() {
	m_server = { 0 };
	
	m_server->initialize(6940);

	m_server->set_thread(ClientThread);
	
}