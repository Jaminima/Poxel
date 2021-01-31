#pragma once
#include "Color.h"
#include <amp.h>

using namespace Concurrency;

class Poxel
{
public:
	Color color;
	bool enabled = false;

	Poxel() restrict(amp, cpu) { enabled = true; }

	void setDefault() {
		color = Color(UINT_MAX, UINT_MAX, UINT_MAX);
		enabled = false;
	}

	index<2> doStep(array_view<Poxel, 2> poxel, array_view<Color, 3> rgbView, index<2> idx, bool bufferSwitch) restrict (amp) {
		rgbView[bufferSwitch][idx] = poxel[idx].color;

		/*if (!poxel[idx - px].enabled) {*/
		return index<2>(idx - px);
		//}
	}
};

