#include "stdafx.h"
#include "Player.h"

Player::Player(Graphics* graphics, const D3DXCOLOR& color)
	: Rect(graphics, color)
{
}

Player::~Player()
{
}

void Player::Event()
{
	intersect_color = D3DXCOLOR(1, 0, 0, 1);
}

void Player::Update()
{
	__super::Update();

	intersect_color = D3DXCOLOR(1, 1, 1, 1);
}

void Player::Move()
{
	if (GetAsyncKeyState('W') & 0x8000) position.y++;
	else if (GetAsyncKeyState('A') & 0x8000) position.x--;
	if (GetAsyncKeyState('S') & 0x8000) position.y--;
	else if (GetAsyncKeyState('D') & 0x8000) position.x++;
}
