#include "Block.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Map.h"
#include "Buffer.h"

#define Nextx 14
#define Nexty 5

using namespace std;

	Map::Map()
	{
		for (int i = 0; i < 20; i++) {
			map[0][i] = 2;
			map[23][i] = 2;
			if (i >= 11) map[9][i] = 2;
		}
		for (int i = 0; i < 24; i++) {
			map[i][0] = 2;
			map[i][11] = 2;
			map[i][19] = 2;
		}
		for (int i = 1; i < 11; i++) {
			map[2][i] = 4;
		}
		for (int i = 0; i < 24; i++) {
			for (int t = 0; t < 20; t++) {
				gotoxy(t, i);
				switch (map[i][t])
				{
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "бс";
					break;
				case 2:
					cout << "в╞";
					break;
				case 3:
					cout << "бр";
					break;
				case 4:
					cout << ".";
					break;
				}
				copymap[i][t] = map[i][t];
			}
		}
	}

	bool Map::Rotationcheck(Block block, int x, int y)
	{
	    int arr[4][4];
		block.Rotation(0);
		block.Copy(arr);
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				if (arr[i][t] == 1) {
					if (map[i + y][t + x] == 2 || map[i + y][t + x] == 3) {
						block.Rotation(1);
						return false;
					}
				}
			}
		}
		return true;
	}

	bool Map::Movecheck(Block block, int x, int y, int direction)
	{
		int arr[4][4];
		block.Copy(arr);
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				if (arr[i][t] == 1) {
					if (map[i + y][t + x + direction] == 2 || map[i + y][t + x + direction] == 3) {
						return false;
					}
				}
			}
		}
		return true;
	}
	bool Map::Crashcheck(Block block, int x, int y)
	{
		int arr[4][4];
		block.Copy(arr);
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				if (arr[i][t] == 1) {
					if (map[i + y + 1][t + x] == 2 || map[i + y + 1][t + x] == 3) {
						return true;
					}
				}
			}
		}
		return false;
	}
	int Map::Crash(Block *block, int &x, int &y)
	{
		int arr[4][4];
		int check = 0;
		int delay = 0;
		while (delay < 10)
		{
			if (_kbhit())
			{
				int input = _getch();
				switch (input)
				{
				case 75:
					if (Movecheck(*block, x, y, -1))
					{
						check++;
						x--;
						Draw(*block,x,y);
						block->Next(Nextx, Nexty);
					}
					break;
				case 72:
					if (Rotationcheck(*block, x, y))
					{
						check++;
						block->Rotation(0);
						Draw(*block,x,y);
						block->Next(Nextx, Nexty);
					}
					else
					{
						if (Rotationcheck(*block, x, y - 1))
						{
							check++;
							y--;
							block->Rotation(0);
							Draw(*block,x,y);
							block->Next(Nextx, Nexty);
						}
					}
					break;
				case 77:
					if (Movecheck(*block, x, y, 1))
					{
						check++;
						x++;
						Draw(*block,x,y);
						block->Next(Nextx, Nexty);
					}
					break;
				}
			}
			if (!Crashcheck(*block, x, y)) return 0;
			Sleep(50);
			delay++;
		}
		while (_kbhit()) _getch();
		if (!Crashcheck(*block, x, y)) return 0;
		block->Copy(arr);
		for (int j = 0; j < 4; j++) {
			for (int s = 0; s < 4; s++) {
				if (arr[j][s] == 1) map[j + y][s + x] = 3;
			}
		}
		return 1;
	}
	void Map::Draw(Block block, int x, int y)
	{
		int arr[4][4];
		block.Copy(arr);
		for (int i = 1; i < 11; i++) {
			map[2][i] = 4;
		}
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				if (map[i + y][t + x] == 0|| map[i + y][t + x] == 4) map[i + y][t + x] = arr[i][t];
			}
		}
		for (int i = 0; i < 24; i++) {
			for (int t = 0; t < 20; t++) {
				if (copymap[i][t] != map[i][t])
				{
					gotoxy(t, i);
					switch (map[i][t])
					{
					case 0:
						cout << " ";
						break;
					case 1:
						cout << "бс";
						break;
					case 2:
						cout << "в╞";
						break;
					case 3:
						cout << "бр";
						break;
					case 4:
						cout << ".";
						break;
					}
					copymap[i][t] = map[i][t];
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				if (map[i + y][t + x] == 1) map[i + y][t + x] = 0;
			}
		}
	}
	void Map::Linecheck(Block block, int y)
	{
		int arr[4][4];
		int max = 0;
		block.Copy(arr);
		for (int j = 0; j < 4; j++) {
			for (int s = 0; s < 4; s++) {
				if (arr[j][s] == 1) max = j;
			}
		}
		int check = 0;
		int Line[4] = { 0, };
		for (int i = y; i < y+max+1; i++) {
			int cnt = 0;
			for (int t = 1; t < 11; t++) {
				if (map[i][t] == 3) cnt++;
			}
			if (cnt == 10) check++, Line[i - y] = 1;
		}
		if (check == 0) return;
		for(int k=3;k>=0;k--)
		{
			if (Line[k] == 1)
			{
				int tempmap[26][12];
				for (int i = 0; i < y + max + 1; i++) {
					for (int t = 1; t < 11; t++) {
						tempmap[i][t] = map[i][t];
					}
				}
				for (int i = 3; i < y+k; i++) {
					for (int t = 1; t < 11; t++) {
						map[i + 1][t] = tempmap[i][t];
					}
				}
				y++;
			}
		}
	}
	int Map::Drop(Block block, int x, int y)
	{
		int arr[4][4];
		block.Copy(arr);
		while (!Crashcheck(block, x, y)) y++;
		for (int j = 0; j < 4; j++) {
			for (int s = 0; s < 4; s++) {
				if (arr[j][s] == 1) map[j + y][s + x] = 3;
			}
		}
		return y;
	}
	bool Map::Gameover()
	{
		for (int i = 1; i < 3; i++) {
			for (int t = 1; t < 11; t++) {
				if (map[i][t] == 3) return true;
			}
		}
		return false;
	}
	void Map::newDraw(Block block, int x, int y)
	{
		int arr[4][4];
		block.Copy(arr);
		for (int i = 1; i < 11; i++) {
			map[2][i] = 4;
		}
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				if (map[i + y][t + x] == 0 || map[i + y][t + x] == 4) map[i + y][t + x] = arr[i][t];
			}
		}
		for (int i = 0; i < 24; i++) {
			for (int t = 0; t < 20; t++) {
				gotoxy(t, i);
				switch (map[i][t])
				{
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "бс";
					break;
				case 2:
					cout << "в╞";
					break;
				case 3:
					cout << "бр";
					break;
				case 4:
					cout << ".";
					break;
				}
				copymap[i][t] = map[i][t];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				if (map[i + y][t + x] == 1) map[i + y][t + x] = 0;
			}
		}
	}