#pragma once
#include "GL/glut.h"
#include "Voxler.h"

bool leftDown, rightDown;

unsigned int brushNum = 0;
Color brushColors[]{ Color(UINT_MAX,0,0), Color(0,UINT_MAX,0), Color(0,0,UINT_MAX), Color(0,UINT_MAX,UINT_MAX), Color(UINT_MAX,0,UINT_MAX), Color(UINT_MAX,UINT_MAX,0) };

void mouseMovingDepressed(int x, int y) {
	if (leftDown) doBrushPlace(x, y, Poxel(brushColors[brushNum]));
	if (rightDown) doBrushDelete(x, y);
}

void mouseDepressed(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			doBrushPlace(x, y, Poxel(brushColors[brushNum]));
			leftDown = true;
		}

		if (button == GLUT_RIGHT_BUTTON) {
			doBrushDelete(x, y);
			rightDown = true;
		}

		if (button == GLUT_MIDDLE_BUTTON) {
			brushNum = (brushNum + 1) % (sizeof(brushColors) / sizeof(Color));
		}
	}
	else {
		if (button == GLUT_LEFT_BUTTON) leftDown = false;
		if (button == GLUT_RIGHT_BUTTON) rightDown = false;
	}
}
