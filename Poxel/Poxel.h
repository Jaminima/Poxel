#pragma once
#include "Color.h"
#include <amp.h>

using namespace Concurrency;

class Poxel
{
public:
	Color color;
	bool enabled = false;

	Poxel() restrict(amp,cpu) {}

	void setDefault() {
		color = Color(UINT_MAX, UINT_MAX, UINT_MAX);
		enabled = false;
	}

	void doStep(array_view<Poxel, 2> poxel, array_view<Color, 3> rgbView, index<2> idx, bool bufferSwitch) restrict (amp) {
		rgbView[bufferSwitch][idx] = poxel[idx].color;

		if (idx[0] > 0) { //Prevent falling out of scene

			if (!poxel[idx[0] - 1][idx[1]].enabled) {
				Poxel* p = &poxel[idx[0] - 1][idx[1]];

				p->enabled = true;
				p->color = color;

				enabled = false;
			}

		}
	}
};

