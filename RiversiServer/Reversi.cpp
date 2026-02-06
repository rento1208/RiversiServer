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
	int brack = GetColor(0, 0, 0);
	int white = GetColor(255, 255, 255);
	int green = GetColor(0, 128, 0);

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			int drawX = Offset + x * CellSize;
			int drawY = Offset + y * CellSize;

			// ƒ}ƒX–Ú‚Ì•`‰æ
			DrawBox(drawX, drawY, drawX + CellSize, drawY + CellSize, green, TRUE);
			DrawBox(drawX, drawY, drawX + CellSize, drawY + CellSize,brack, FALSE);

			// Î‚Ì•`‰æ
			if (board[y][x] == 1)
			{
				DrawCircle(drawX + CellSize / 2, drawY + CellSize / 2, CellSize / 2 - 5, white, TRUE);
			}
			if (board[y][x] == 2)
			{
				DrawCircle(drawX + CellSize / 2, drawY + CellSize / 2, CellSize / 2 - 5, brack, TRUE);
			}
		}
	}

	ScreenFlip();
}

bool Reversi::CapPut(int x, int y)
{
	return(x >= 0 && x < 8 && y >= 0 && y < 8 && board[y][x] == 0);
}

void Reversi::Put(int x, int y, int color)
{
	board[y][x] = color;
}
