#include "LiveOperate.h"
#include <iostream>
using namespace std;

LiveOperate::LiveOperate()
{
}


LiveOperate::~LiveOperate()
{
	if (_world != NULL)
	{
		clear();
	}
}

void LiveOperate::init(int r, int c)
{
	_rows = r;
	_cols = c;

	_world = new int*[_rows];
	for (int i = 0; i < _rows; ++i)
	{
		int* temp = new int[_cols];
		for (int j = 0; j < _cols; ++j)
		{
			temp[j] = false;
		}
		_world[i] = temp;
	}
	
	randomInit();
	
}
void LiveOperate::updateLive()
{
	int** new_wold = new int*[_rows];
	for (int r = 0; r < _rows; ++r)
	{
		int* temp = new int[_cols];
		for (int c = 0; c < _cols; ++c)
		{
			Point pos(r, c);
			temp[c] = checkLive(pos);
		}
		new_wold[r] = temp;
	}
	//更新旧世界：
	clear();
	_world = new_wold;
}

void LiveOperate::clear()
{
	if (_world != NULL)
	{
		for (int i = 0; i < _rows; ++i)
		{
			delete[] _world[i];
			_world[i] = NULL;
		}
		delete[] _world;
		_world = NULL;
	}
}

bool LiveOperate::checkLive(Point pos)
{
	int alive_sum = 0;
	for (int j = pos.y - 1; j <= pos.y + 1 && j < _rows; ++j)
	{
		if (j < 0)
		{
			continue;
		}
		
		for (int i = pos.x - 1; i <= pos.x + 1 && i < _cols; ++i)
		{
			if (i < 0)
			{
				continue;
			}
			
			if (_world[j][i])
			{
				alive_sum++;
			}
		}
	}
	if (_world[pos.x][pos.y])
	{
		alive_sum -= 1;
	}
	if (alive_sum == 3)
	{
		return true;
	}
	else if(alive_sum == 2)
	{
		return _world[pos.x][pos.y];
	}
	else
	{
		return false;
	}
}

void LiveOperate::showWorld()
{
	for (int i = 0; i < _cols; ++i)
	{
		for (int j = 0; j < _rows; ++j)
		{
			cout << _world[i][j] << " ";
		}
		cout << endl;
	}
}

void LiveOperate::randomInit() {	
	srand((unsigned)time(NULL));	

	for (int i = 0; i < _rows; ++i)
	{	
		for (int j = 0; j < _cols; ++j)
		{ 
			int temp = rand() % 2;			
			_world[i][j] = temp;
		}
	}
}

bool LiveOperate::getWorld(int x, int y) {

	return _world[x][y];
}

int LiveOperate::getRows()
{
	return _rows;
}
void LiveOperate::setRows(int rows)
{
	_rows = rows;
}
int LiveOperate::getCols() 
{
	return _cols;
}
void LiveOperate::setCols(int cols)
{
	_cols = cols;
}