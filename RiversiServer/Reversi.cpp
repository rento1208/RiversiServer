#include "Reversi.h"

Reversi::Reversi()
	: cellSize(60), Offset(50), board()
{
	

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			board[y][x] = 0;
			board[3][3] = 2;
			board[3][4] = 1;
			board[4][3] = 1;
			board[4][4] = 2;
		}
	}
}

Reversi::~Reversi()
{
}

void Reversi::Draw()
{
	ClearDrawScreen();
	int Brack = GetColor(0, 0, 0);
	int White = GetColor(255, 255, 255);
	int Green = GetColor(0, 128, 0);

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			int drawX = Offset + x * CellSize;
			int drawY = Offset + y * CellSize;

			// ƒ}ƒX–Ú‚Ì•`‰æ
			DrawBox(drawX, drawY, drawX + CellSize, drawY + CellSize, Green, TRUE);
			DrawBox(drawX, drawY, drawX + CellSize, drawY + CellSize,Brack, FALSE);

			// Î‚Ì•`‰æ
			if (board[y][x] == 1)
			{
				DrawCircle(drawX + CellSize / 2, drawY + CellSize / 2, CellSize / 2 - 5, White, TRUE);
			}
			if (board[y][x] == 2)
			{
				DrawCircle(drawX + CellSize / 2, drawY + CellSize / 2, CellSize / 2 - 5, Brack, TRUE);
			}
		}
	}

	ScreenFlip();
}

bool Reversi::CanPut(int x, int y)
{
    
	return(x >= 0 && x < 8 && y >= 0 && y < 8 && board[y][x] == 0);
}

void Reversi::Put(int x, int y, int color)
{
	board[y][x] = color;
}
