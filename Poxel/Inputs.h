#pragma once
#include "GL/glut.h"
#include "Voxler.h"

void mouseMovingDepressed(int x, int y) {
	poxels[x + ((py-y)*px)].enabled = true;
}