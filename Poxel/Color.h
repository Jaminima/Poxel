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

	Color() restrict(amp,cpu) {
		colors.r = 0;
		colors.g = 0;
		colors.b = 0;
		colors.a = UINT_MAX;
	}

	Color(unsigned int r, unsigned int g, unsigned int b) restrict(amp, cpu) {
		colors.r = r;
		colors.g = g;
		colors.b = b;
		colors.a = UINT_MAX;
	}
};

