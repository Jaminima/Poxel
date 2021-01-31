#pragma once
#include <amp.h>

using namespace Concurrency;

class Color
{
public:
	union {
		struct _colors {
			unsigned int r, g, b, a;
		} colors;

		unsigned int rgba[4];
	};

	Color() {
		colors.r = 0;
		colors.g = 0;
		colors.b = 0;
		colors.a = UINT_MAX;
	}
};

