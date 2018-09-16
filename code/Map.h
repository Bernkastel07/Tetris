#pragma once
#include "Block.h"

class Map
{
private: int map[24][20] = { 0, };
		 int copymap[24][20] = { 0, };
public: Map();
		bool Rotationcheck(Block block, int x, int y);
		bool Movecheck(Block block, int x, int y, int direction);
		bool Crashcheck(Block block, int x, int y);
		int Crash(Block *block, int &x, int &y);
		void Draw(Block block,int x, int y);
		void Linecheck(Block block, int y);
		int Drop(Block block, int x, int y);
		bool Gameover();
		void newDraw(Block block, int x, int y);
};