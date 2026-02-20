#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <cstdio>
#include <winsock2.h>
#include <DxLib.h>
#include "Reversi.h"

#pragma comment(lib,"ws2_32.lib")

int WINAPI main(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, 1);

    u_long mode = 1;
    ioctlsocket(server, FIONBIO, &mode);

    sockaddr_in clientAddr{};
    int clientAddrSize = sizeof(clientAddr);
    SOCKET client = accept(server, (sockaddr*)&clientAddr, &clientAddrSize);


    Reversi game;

    int oldMouse = 0;

    while (ProcessMessage() == 0)
    {
        char buf[16] = {};

        //相手（クライアント）の手受信
        int recvSize = recv(client, buf, sizeof(buf) - 1, 0);
        if (recvSize > 0)
        {
            buf[recvSize] = '\0';

            int rx, ry;
            if (sscanf_s(buf, "%d %d", &rx, &ry) == 2)
            {
                game.Put(rx, ry, 2);  // クライアントは白
            }
        }

        //自分（サーバー側）のクリック
        int nowMouse = GetMouseInput();

        if ((nowMouse & MOUSE_INPUT_LEFT) &&
            !(oldMouse & MOUSE_INPUT_LEFT))
        {
            int mx, my;
            GetMousePoint(&mx, &my);

            int cell = game.GetCellSize();
            int offsetX = game.GetOffsetX();
            int offsetY = game.GetOffsetY();
            int boardSize = cell * 8;

            if (mx >= offsetX &&
                mx < offsetX + boardSize &&
                my >= offsetY &&
                my < offsetY + boardSize)
            {
                int x = (mx - offsetX) / cell;
                int y = (my - offsetY) / cell;

                if (game.CanPut(x, y))
                {
                    game.Put(x, y, 1);  // サーバーは黒

                    sprintf_s(buf, "%d %d", x, y);
                    send(client, buf, strlen(buf) + 1, 0);
                }
            }
        }

        oldMouse = nowMouse;

        game.Draw();
    }

    closesocket(client);
    closesocket(server);
    WSACleanup();
    DxLib_End();
    return 0;
}