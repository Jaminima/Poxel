#pragma once

#include "Poxel.h"
#include <amp.h>

using namespace Concurrency;

Poxel* poxels = static_cast<Poxel*>(malloc(2 * px * py * sizeof(Poxel)));

void ensureDefaults() {
	for (unsigned int i = 0; i < px * py; i++)
		poxels[i].setDefault();
}

void doBrushDelete(unsigned int x, unsigned int y) {
	for (unsigned int _x = x - brushSize, _y = y - brushSize; _y < y + brushSize;) {

		if (_x >= 0 && _x < px && _y >= 0 && _y < py) {
			poxels[_x + ((py - _y) * px)] = Poxel();
		}

		_x++;
		if (_x == x + brushSize) { _x = x - brushSize; _y++; }
	}
}

void doBrushPlace(unsigned int x, unsigned int y, Poxel pox) {
	for (unsigned int _x = x - brushSize, _y = y - brushSize; _y < y + brushSize;) {

		if (_x >= 0 && _x < px && _y >= 0 && _y < py) {
			Poxel p(pox);
			p.enabled = true;
			poxels[_x + ((py - _y) * px)] = p;
		}

		_x++;
		if (_x == x + brushSize) { _x = x - brushSize; _y++; }
	}
}

completion_future processTick(array_view<Color, 3> rgbView, bool bufferSwitch) {
	Color _bgColor = bgColor;
	array_view<Poxel, 2> poxel(py, px, poxels);

	parallel_for_each(
		poxel.extent,
		[=](index<2> idx) restrict(amp) {
			if (poxel[idx].enabled) {
				poxel[idx].doStep(poxel, rgbView, idx, bufferSwitch);
			}
			else rgbView[bufferSwitch][idx] = _bgColor;
		}
	);

	return poxel.synchronize_async();
}
