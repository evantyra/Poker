#include "Frame.h"
#include <iostream>

using namespace std;


Frame::Frame(){
	x = 0;
	y = 0;
}

Frame::~Frame(){}

Frame::Frame(int xx, int yy, int w, int h){
	x = xx;
	y = yy;
	width = w;
	height = h;
}

int Frame::getX(){return x;}

void Frame::setX(int xx){x = xx;}

int Frame::getY(){return y;}

void Frame::setY(int yy){y = yy;}

int Frame::getWidth(){return width;}

int Frame::getHeight(){return height;}
