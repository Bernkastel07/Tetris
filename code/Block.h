#pragma once
void gotoxy(int x, int y);

class Block
{
private: int block[4][4] = { 0, };
		 int nextblock[4][4] = { 0, };
		 int copyblock[4][4] = { 0, };
		 int next = 0;
		 int now = 0;
		 int direction = 0;
		 int tempdirection = 0;
public:
	Block();
	void Make();
	void Next(int x, int y);
	void Rotation(int a);
	void Print(int x, int y);
	void Copy(int arr[][4]);
};