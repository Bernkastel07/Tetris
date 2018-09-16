#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include "Buffer.h"
#include "Block.h"

void gotoxy(int x, int y)
{
	COORD Pos = { 2*x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


using namespace std;

	Block::Block()
	{
		srand((unsigned int)time(NULL));
		next = rand() % 7;
		now = next;
	}
	void Block::Make()
	{
		now = next;
		next = rand() % 7;
		direction = 0;
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				block[i][t] = 0;
			}
		}
		switch (now)
		{
		case 0:	
			block[1][0] = 1, block[1][1] = 1, block[1][2] = 1, block[1][3] = 1;
			break;
		case 1:
			block[1][0] = 1, block[1][1] = 1, block[1][2] = 1, block[0][2] = 1;
			break;
		case 2:
			block[1][0] = 1, block[1][1] = 1, block[0][1] = 1, block[0][2] = 1;
			break;
		case 3:
			block[0][0] = 1, block[0][1] = 1, block[1][1] = 1, block[1][2] = 1;
			break;
		case 4:
			block[1][0] = 1, block[1][1] = 1, block[1][2] = 1, block[0][0] = 1;
			break;
		case 5:
			block[1][1] = 1, block[1][2] = 1, block[0][1] = 1, block[0][2] = 1;
			break;
		case 6:
			block[0][1] = 1, block[1][0] = 1, block[1][1] = 1, block[1][2] = 1;
			break;
		}
		return;
	}
	void Block::Next(int x, int y)
	{
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				nextblock[i][t] = 0;
			}
		}
		switch (next)
		{
		case 0:
			nextblock[1][0] = 1, nextblock[1][1] = 1, nextblock[1][2] = 1, nextblock[1][3] = 1;
			break;
		case 1:
			nextblock[1][0] = 1, nextblock[1][1] = 1, nextblock[1][2] = 1, nextblock[0][2] = 1;
			break;
		case 2:
			nextblock[1][0] = 1, nextblock[1][1] = 1, nextblock[0][1] = 1, nextblock[0][2] = 1;
			break;
		case 3:
			nextblock[0][0] = 1, nextblock[0][1] = 1, nextblock[1][1] = 1, nextblock[1][2] = 1;
			break;
		case 4:
			nextblock[1][0] = 1, nextblock[1][1] = 1, nextblock[1][2] = 1, nextblock[0][0] = 1;
			break;
		case 5:
			nextblock[1][1] = 1, nextblock[1][2] = 1, nextblock[0][1] = 1, nextblock[0][2] = 1;
			break;
		case 6:
			nextblock[0][1] = 1, nextblock[1][0] = 1, nextblock[1][1] = 1, nextblock[1][2] = 1;
			break;
		}
		gotoxy(x, y);
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				if (nextblock[i][t]==1) {
					gotoxy(t + x, i + y);
					cout << "бс";
				}
				else gotoxy(t + x, i + y), cout << " ";
			}
		}
	}
	void Block::Rotation(int a)
	{
		if (a == 1) direction = tempdirection;
		else {
			tempdirection = direction++;
			direction = direction % 4;
			for (int i = 0; i < 4; i++) {
				for (int t = 0; t < 4; t++) {
					block[i][t] = 0;
				}
			}
		}
		switch (now)
		{
		case 0:
			switch (direction)
			{
			case 0: block[1][0] = 1, block[1][1] = 1, block[1][2] = 1, block[1][3] = 1;
				break;
			case 1: block[0][1] = 1, block[1][1] = 1, block[2][1] = 1, block[3][1] = 1;
				break;
			case 2: block[1][0] = 1, block[1][1] = 1, block[1][2] = 1, block[1][3] = 1;
				break;
			case 3: block[0][1] = 1, block[1][1] = 1, block[2][1] = 1, block[3][1] = 1;
				break;
			}
			break;
		case 1:
			switch (direction)
			{
			case 0: block[1][0] = 1, block[1][1] = 1, block[1][2] = 1, block[0][2] = 1;
				break;
			case 1: block[0][1] = 1, block[1][1] = 1, block[2][1] = 1, block[2][2] = 1;
				break;
			case 2: block[1][0] = 1, block[1][1] = 1, block[1][2] = 1, block[2][0] = 1;
				break;
			case 3: block[0][0] = 1, block[0][1] = 1, block[1][1] = 1, block[2][1] = 1;
				break;
			}
			break;
		case 2:
			switch (direction)
			{
			case 0: block[1][0] = 1, block[1][1] = 1, block[0][1] = 1, block[0][2] = 1;
				break;
			case 1: block[0][1] = 1, block[1][1] = 1, block[1][2] = 1, block[2][2] = 1;
				break;
			case 2: block[1][0] = 1, block[1][1] = 1, block[0][1] = 1, block[0][2] = 1;
				break;
			case 3: block[0][1] = 1, block[1][1] = 1, block[1][2] = 1, block[2][2] = 1;
				break;
			}
			break;
		case 3:
			switch (direction)
			{
			case 0: block[0][0] = 1, block[0][1] = 1, block[1][1] = 1, block[1][2] = 1;
				break;
			case 1: block[0][2] = 1, block[1][1] = 1, block[1][2] = 1, block[2][1] = 1;
				break;
			case 2: block[0][0] = 1, block[0][1] = 1, block[1][1] = 1, block[1][2] = 1;
				break;
			case 3: block[0][2] = 1, block[1][1] = 1, block[1][2] = 1, block[2][1] = 1;
				break;
			}
			break;
		case 4:
			switch (direction)
			{
			case 0: block[1][0] = 1, block[1][1] = 1, block[1][2] = 1, block[0][0] = 1;
				break;
			case 1: block[0][1] = 1, block[1][1] = 1, block[0][2] = 1, block[2][1] = 1;
				break;
			case 2: block[1][0] = 1, block[1][1] = 1, block[1][2] = 1, block[2][2] = 1;
				break;
			case 3: block[0][1] = 1, block[1][1] = 1, block[2][0] = 1, block[2][1] = 1;
				break;
			}
			break;
		case 5:
			block[1][1] = 1, block[1][2] = 1, block[0][1] = 1, block[0][2] = 1;
			break;
		case 6:
			switch (direction)
			{
			case 0: block[0][1] = 1, block[1][0] = 1, block[1][1] = 1, block[1][2] = 1;
				break;
			case 1: block[0][1] = 1, block[1][1] = 1, block[2][1] = 1, block[1][2] = 1;
				break;
			case 2: block[2][1] = 1, block[1][0] = 1, block[1][1] = 1, block[1][2] = 1;
				break;
			case 3: block[0][1] = 1, block[1][1] = 1, block[2][1] = 1, block[1][0] = 1;
				break;
			}
			break;
		}
	}
	void Block::Print(int x, int y) 
	{
		for (int i = 0; i < 4; i++){
			for (int t = 0; t < 4; t++) {
				if (block[i][t] == 1) {
					gotoxy(x + t, y + i);
					cout << "бс";
				}
			}
		}
	}
	void Block::Copy(int arr[][4])
	{
		for (int i = 0; i < 4; i++) {
			for (int t = 0; t < 4; t++) {
				arr[i][t] = block[i][t];
			}
		}
	}