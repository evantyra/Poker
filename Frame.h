#pragma once

using namespace std;

class Frame
{
private:
	int x, y, width, height;
public:
	Frame();
	Frame(int xx, int yy, int w, int h);
	int getX();
	void setX(int xx);
	int getY();
	void setY(int yy);
	int getWidth();
	int getHeight();
	~Frame(void);
};

