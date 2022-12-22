#include "stdafx.h"
#include "Monster.h"

Monster::Monster(Graphics* graphics, const D3DXCOLOR& color)
	: Rect(graphics, color)
{
}

Monster::~Monster()
{
}

void Monster::Move()
{
	static Direction dir = Direction::Right;

	static std::random_device rd;
	static std::mt19937 mt(rd());
	static std::uniform_int_distribution<int> rand(0, 3);

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

	if (work_time.count() >= 1000.0)
	{
		Direction new_dir = static_cast<Direction>(rand(mt));

		if (new_dir == dir)
		{
			int dir_num = static_cast<int>(dir);

			dir_num = (dir_num <= 1) ? dir_num + 2 : dir_num - 2;

			dir = static_cast<Direction>(dir_num);
		}
		else
			dir = new_dir;

		check_time = std::chrono::system_clock::now();
	}
}
