#pragma once
#include "GL/glut.h"
#include "Voxler.h"

void mouseMovingDepressed(int x, int y) {
	doBrushPlace(x, y);
}

void mouseDepressed(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			doBrushPlace(x, y);
		}
	}
}
