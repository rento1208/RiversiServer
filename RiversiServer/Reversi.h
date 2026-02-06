#pragma once
#include <DxLib.h>

class Reversi
{
public:
	Reversi();
	~Reversi();
	void Draw();
	bool CanPut(int x, int y);
	void Put(int x, int y, int color);

private:
	int board[8][8];
	int cellSize;
    int CellSize;
	int Offset;
};