#pragma once

#include <chrono>

std::chrono::time_point<std::chrono::high_resolution_clock> nowTick;

void startTick()
{
	nowTick = std::chrono::high_resolution_clock::now();
}

int64_t getTick()
{
	int64_t tick = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - nowTick).count();
	nowTick = std::chrono::high_resolution_clock::now();

	return tick;
}