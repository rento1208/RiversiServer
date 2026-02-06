#include <DxLib.h>  
#include <winsock2.h>  
#include "Reversi.h"  

#pragma comment(lib,"ws2_32.lib")  

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ChangeWindowMode(TRUE);
	DxLib_Init();

	// WinSockの初期化  
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(server, (sockaddr*)&addr, sizeof(addr));
	listen(server, 1);

	sockaddr_in clientAddr;
	int clientAddrSize = sizeof(clientAddr);
	SOCKET client = accept(server, (sockaddr*)&clientAddr, &clientAddrSize);

	Reversi game;

	
	while (ProcessMessage() == 0)
	{
		game.Draw();

		int mx, my;
		GetMousePoint(&mx, &my);

		int x = (mx - 50) / 60;
		int y = (my - 50) / 60;

		if (game.CanPut(x, y))
		{
			game.Put(x, y, 1);

			char buf[16];
			sprintf_s(buf, "%d,%d", x, y);
			send(client, buf, strlen(buf) + 1, 0);

			recv(client, buf, sizeof(buf), 0);
			sscanf_s(buf, "%d,%d", &x, &y);
			game.Put(x, y, 2);

		}
		
    }

   closesocket(client);  
   closesocket(server);  
   WSACleanup();  
   DxLib_End();

   return 0;  
}