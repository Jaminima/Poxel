#pragma once

#include "Poxel.h"
#include <amp.h>

using namespace Concurrency;

	Poxel* poxels = static_cast<Poxel*>(malloc(px * py * sizeof(Poxel)));	

	void ensureDefaults() {
		for (unsigned int i = 0; i < px * py; i++) 
			poxels[i].setDefault();
	}

	void processTick(array_view<Color, 3> rgbView, bool bufferSwitch) {
		poxels[250 + (py*100)].enabled = true;

		array_view<Poxel, 2> poxel(py, px, poxels);

		parallel_for_each(
			poxel.extent,
			[=](index<2> idx) restrict(amp) {
				if (poxel[idx].enabled) {
					index<2> p = poxel[idx].doStep(poxel, rgbView, idx, bufferSwitch);
					poxel[p].enabled = true;
				}
			}
		);

		poxel.synchronize();
	}