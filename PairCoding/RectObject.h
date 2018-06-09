#pragma once
class RectObject
{
public:
	RectObject();
	~RectObject();

	int x = 0;
	int y = 0;
	int length = 50;
	bool life = false;
	bool child_life = false;

	void _setLife();
	void _setChildLife(bool my_life);
};

