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
	for (int row = 0; row < _rows; ++row)
	{
		int* temp = new int[_cols];
		for (int col = 0; col < _cols; ++col)
		{
			temp[col] = checkLive(row, col);
		}
		new_wold[row] = temp;
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

int LiveOperate::collectAliveNaber(int x, int y)
{
	int alive_sum = 0;
	for (int i = x - 1; i <= x + 1 && i < _rows; ++i)
	{
		if (i < 0)
		{
			continue;
		}
		for (int j = y - 1; j <= y + 1 && j < _cols; ++j)
		{
			if (j < 0)
			{
				continue;
			}

			if (_world[i][j])
			{
				alive_sum++;
			}
		}
	}
	if (_world[x][y])
	{
		alive_sum -= 1;
	}
	return alive_sum;
}

bool LiveOperate::checkLive(int x, int y)
{
	int alive_sum = collectAliveNaber(x, y);
	
	if (alive_sum == 3)
	{
		return true;
	}
	else if(alive_sum == 2)
	{
		return _world[x][y];
	}
	else
	{
		return false;
	}
}

void LiveOperate::setWorld(int oldWorld[][5], int rows, int cols)
{
	_world = new int*[rows];
	for (int i = 0; i < rows; i++)
	{
		int* temp = new int[cols];
		for (int j = 0; j < cols; ++j)
		{
			temp[j] = oldWorld[i][j];
		}
		_world[i] = temp;
	}
	_rows = rows;
	_cols = cols;
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