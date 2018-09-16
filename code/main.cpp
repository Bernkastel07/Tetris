#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include "Block.h"
#include "Map.h"

#define Left 75
#define Right 77
#define Up 72
#define Down 80
#define Space 32
#define Nextx 14
#define Nexty 5


int main() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	while (1)
	{
		int x = 4;
		int y = 1;
		Block block;
		Map map;
		gotoxy(14, 2);
		std::cout << "-Next-";
		while (1)
		{
			x = 4;
			y = 1;
			block.Make();
			map.Draw(block, x, y);
			block.Next(Nextx, Nexty);
			int check = 0;
			while (1)
			{
				int drop = 0;
				for (int i = 0; i < 20; i++)
				{
					if (_kbhit())
					{
						int input = _getch();
						switch (input)
						{
						case Left:
							if (map.Movecheck(block, x, y, -1))
							{
								x--;
								map.Draw(block, x, y);
								block.Next(Nextx, Nexty);
							}
							break;
						case Right:
							if (map.Movecheck(block, x, y, 1))
							{
								x++;
								map.Draw(block, x, y);
								block.Next(Nextx, Nexty);
							}
							break;
						case Up:
							if (map.Rotationcheck(block, x, y))
							{
								block.Rotation(0);
								map.Draw(block, x, y);
								block.Next(Nextx, Nexty);
							}
							break;
						case Down:
							if (!map.Crashcheck(block, x, y))
							{
								y++;
								map.Draw(block, x, y);
								block.Next(Nextx, Nexty);
							}
							break;
						case Space:
							y = map.Drop(block, x, y);
							drop = 1;
							break;
						case 112:
							gotoxy(9, 12);
							std::cout << "pause";
							_getch();
							system("cls");
							map.newDraw(block, x, y);
							block.Next(Nextx, Nexty);
							gotoxy(14, 2);
							std::cout << "-Next-";
							break;
						}
					}
					if (drop == 1) break;
					Sleep(25);
				}
				while (_kbhit()) _getch();
				if (drop == 1) break;
				if (map.Crashcheck(block, x, y))
				{
					int crash = map.Crash(&block, x, y);
					if (crash == 1) break;
					else continue;
				}
				y++;//시간이 지남에따라 한칸내려감
				map.Draw(block, x, y);
				block.Next(Nextx, Nexty);
			}
			map.Linecheck(block, y);
			if (map.Gameover())
			{
				map.Draw(block, x, y);
				block.Next(Nextx, Nexty);
				gotoxy(9, 12);
				std::cout << "Game Over";
				_getch();
				system("cls");
				break;
			}
		}
	}
	return 0;
}