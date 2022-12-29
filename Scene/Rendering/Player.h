#pragma once
#include "Rect.h"

class Player final : public Rect
{
public:
	//using Rect::Rect;
	Player(class Graphics* graphics, const D3DXCOLOR& color);
	~Player();

	void Event() override;
	void Update() override;

protected:
	void Move() override;
};