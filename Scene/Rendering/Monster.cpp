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
	case Direction::Up:
	{
		float height = Settings::Get().GetHeight() / 2;

		if (++position.y >= height - scale.y / 2)
		{
			position.y--;
			dir = Direction::Down;
			stopwatch.Start();
		}

		break;
	}
	case Direction::Right:
	{
		float width = Settings::Get().GetWidth() / 2;

		if (++position.x >= width - scale.x / 2)
		{
			position.x--;
			dir = Direction::Left;
			stopwatch.Start();
		}

		break;
	}
	case Direction::Down:
	{
		float height = Settings::Get().GetHeight() / 2;

		if (--position.y <= -height + scale.y / 2)
		{
			position.y++;
			dir = Direction::Up;
			stopwatch.Start();
		}

		break;
	}
	case Direction::Left:
	{
		float width = Settings::Get().GetWidth() / 2;

		if (--position.x <= -width + scale.x / 2)
		{
			position.x++;
			dir = Direction::Right;
			stopwatch.Start();
		}

		break;
	}
	} // switch (dir)

	if (stopwatch.GetElapsedTimerSec() >= 10.0f)
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