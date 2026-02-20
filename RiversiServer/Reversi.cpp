#include "Reversi.h"


const int Brack = GetColor(0, 0, 0);
const int White = GetColor(255, 255, 255);
const int Green = GetColor(0, 128, 0);
const int Red = GetColor(255, 0, 0);

Reversi::Reversi()
	: cellSize(60), OffsetX(0), OffsetY(0), board()
{
	currentTurn = 2;

	const int screenWidth = 640; //画面の幅
	const int screenHeight = 480; //画面の高さ

	int boardSize = cellSize * 8; //盤面のサイズ

	OffsetX = (screenWidth - boardSize) / 2; //盤面を画面の中央に配置するためのX座標
	OffsetY = (screenHeight - boardSize) / 2; //盤面を画面の中央に配置するためのY座標


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

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			int drawX = OffsetX + x * cellSize;
			int drawY = OffsetY + y * cellSize;
			DrawBox(drawX, drawY,
				drawX + cellSize, drawY + cellSize,
				Green, TRUE);

			// 石の描画
			if (board[y][x] == 1) // 黒
			{
				DrawCircle(drawX + cellSize / 2,
					drawY + cellSize / 2,
					cellSize / 2 - 5,
					Brack, TRUE);
			}
			else if (board[y][x] == 2) // 白
			{
				DrawCircle(drawX + cellSize / 2,
					drawY + cellSize / 2,
					cellSize / 2 - 5,
					White, TRUE);
			}
		}
	}

	// 線を描く
	for (int i = 0; i <= 8; i++)
	{
		int px = OffsetX + i * cellSize;
		int py = OffsetY + i * cellSize;
		DrawLine(OffsetX, py, OffsetX + 8 * cellSize, py, Brack); // 横線
		DrawLine(px, OffsetY, px, OffsetY + 8 * cellSize, Brack); // 縦線
	}

	ScreenFlip();
}




bool Reversi::CanPut(int x, int y)

{
	return(x >= 0 && x < 8 && y >= 0 && y < 8 && board[y][x] == 0);
}

void Reversi::Put(int x, int y, int color)
{
	if (currentTurn != color) return;

	if (CanPut(x, y))
	{
		board[y][x] = color;

		// ターン交代
		currentTurn = (currentTurn == 1) ? 2 : 1;
	}
}

