#pragma once

class Timer final
{
public:

private:
};

class Stopwatch final
{
public:
	Stopwatch();
	~Stopwatch() = default;

	void Start();

	const float GetElapsedTimerSec();
	const float GetElapsedTimerMS();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

