#pragma once
#include "Color.h"

class Poxel
{
public:
	Color color;
	bool enabled = false;

	Poxel() restrict(amp,cpu) {}
};

