#pragma once
#include "Rect.h"

class Monster : public Rect
{
public:
	Monster(class Graphics* graphics, const D3DXCOLOR& color);
	~Monster();

protected:
	void Move() override;
	
private:
	Stopwatch stopwatch;
	Direction dir = Direction::Right;
};