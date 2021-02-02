#pragma once
#include "Const.h"
#include "Color.h"
#include <amp.h>

using namespace Concurrency;

class Poxel
{
public:
	Color color;
	bool enabled = false;

	Poxel() restrict(amp, cpu) {}

	Poxel(Color color) {
		this->color = color;
		enabled = true;
	}

	void setDefault() {
		color = Color(UINT_MAX, UINT_MAX, UINT_MAX);
		enabled = false;
	}

	bool CheckAndSet(array_view<Poxel, 2> poxel, unsigned int y, unsigned int x) restrict(amp,cpu) {
		if (!poxel[y][x].enabled) {
			Poxel* p = &poxel[y][x];

			p->enabled = true;
			p->color = color;

			enabled = false;
			return true;
		}
		return false;
	}

	void doStep(array_view<Poxel, 2> poxel, array_view<Color, 3> rgbView, index<2> idx, bool bufferSwitch) restrict(amp, cpu) {
		rgbView[bufferSwitch][idx] = poxel[idx].color;

		if (idx[0] > 0) { //Prevent falling out of scene
			if (CheckAndSet(poxel, idx[0] - 1, idx[1])) {}
			else if (!(idx[1] == 0 && hardSides) && CheckAndSet(poxel, idx[0] - 1, idx[1] - 1)) {}
			else if (!(idx[1] == px - 1 && hardSides) && CheckAndSet(poxel, idx[0] - 1, idx[1] + 1)) {}
		}
	}
};
