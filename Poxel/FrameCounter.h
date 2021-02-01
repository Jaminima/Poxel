#pragma once
#include <iostream>
#include <Windows.h>

unsigned int framesInSec = 0;
time_t startTime = clock();

void checkFrameTime() {
	if (clock() - startTime >= 1000)
	{
		printf_s("You averaged %d fps\n", framesInSec);
		framesInSec = 0;
		startTime = clock();
	}
}
