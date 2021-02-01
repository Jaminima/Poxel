#pragma once
#include "GL/glut.h"
#include "Voxler.h"

bool leftDown, rightDown;

void mouseMovingDepressed(int x, int y) {
	if (leftDown) doBrushPlace(x, y, Poxel());
	if (rightDown) doBrushDelete(x, y);
}

void mouseDepressed(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			doBrushPlace(x, y, Poxel());
			leftDown = true;
		}

		if (button == GLUT_RIGHT_BUTTON) {
			doBrushDelete(x, y);
			rightDown = true;
		}
	}
	else {
		if (button == GLUT_LEFT_BUTTON) leftDown = false;
		if (button == GLUT_RIGHT_BUTTON) rightDown = false;
	}
}
