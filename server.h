#pragma once
#include "includes.h"

class server
{
public:
	int connectionsindex;
	SOCKET connections[250];

	void* clientThread;


	void initialize(int port);
	void set_thread(void* function);
};

