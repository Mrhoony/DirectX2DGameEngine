#pragma once
#include "Rect.h"

class Player final : public Rect
{
public:
	//using Rect::Rect;
	Player(class Graphics* graphics, const D3DXCOLOR& color);
	~Player();

protected:
	void Move() override;
};