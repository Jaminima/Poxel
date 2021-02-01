#pragma once
#include "GL/glut.h"
#include "Voxler.h"

void mouseMovingDepressed(int x, int y) {
	poxels[x + ((py-y)*px)].enabled = true;
}

void mouseDepressed(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {

		if (button == GLUT_LEFT_BUTTON) {
			poxels[x + ((py - y) * px)].enabled = true;
		}

	}
}