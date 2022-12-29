#include "stdafx.h"
#include "Monster.h"

Monster::Monster(Graphics* graphics, const D3DXCOLOR& color)
	: Rect(graphics, color)
{
	stopwatch.Start();
}

Monster::~Monster()
{
}

void Monster::Event()
{
}

void Monster::Move()
{
	static std::chrono::system_clock::time_point cur_time = std::chrono::system_clock::now();
	static std::chrono::system_clock::time_point check_time = std::chrono::system_clock::now();

	cur_time = std::chrono::system_clock::now();

	std::chrono::duration<double, std::milli> work_time = cur_time - check_time;

	switch (dir)
	{
	case Direction::Up: position.y++;			break;
	case Direction::Right: position.x++;		break;
	case Direction::Down: position.y--;			break;
	case Direction::Left: position.y++;			break;
	}

	if (stopwatch.GetElapsedTimerSec() >= 3.0f)
	{
		Direction new_dir = static_cast<Direction>(Math::Random(0, 3));

		if (new_dir == dir)
		{
			int dir_num = static_cast<int>(dir);

			dir_num = (dir_num <= 1) ? dir_num + 2 : dir_num - 2;

			dir = static_cast<Direction>(dir_num);
		}
		else
			dir = new_dir;

		stopwatch.Start();
	}
}