#pragma once

#include "Poxel.h"
#include <amp.h>

using namespace Concurrency;

	Poxel* poxels = static_cast<Poxel*>(malloc(px * py * sizeof(Poxel)));

	void processTick(array_view<Color, 3> rgbView, bool bufferSwitch) {
		array_view<Poxel, 2> poxel(py, px, poxels);

		parallel_for_each(
			poxel.extent,
			[=](index<2> idx) restrict(amp) {
				rgbView[bufferSwitch][idx].colors.r = UINT_MAX;
				poxel[idx].enabled = true;
			}
		);
	}