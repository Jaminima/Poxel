#pragma once
#include "GL/glut.h"
#include "GL/freeglut.h"

#include "Color.h"
#include "Const.h"
#include "Voxler.h"
#include "Inputs.h"
#include "FrameCounter.h"

bool BufferSwitch = false;
Color* rgbBuffer = static_cast<Color*>(malloc(px * py * 2 * sizeof(Color)));
array_view<Color, 3> rgbView(2, py, px, rgbBuffer);

completion_future pendingFrameCopy;
completion_future pendingPoxelCopy;

void drawFrame() {
	glDrawPixels(px, py, GL_RGBA, GL_UNSIGNED_INT, &rgbBuffer[!BufferSwitch * px * py]);
	glutSwapBuffers();
}

void triggerReDraw()
{
	pendingFrameCopy = rgbView.synchronize_async();

	pendingPoxelCopy = processTick(rgbView, BufferSwitch);

	framesInSec++;
	checkFrameTime();

	glutPostRedisplay();

	BufferSwitch = !BufferSwitch;

	pendingPoxelCopy.wait();
	pendingFrameCopy.wait();
}

void Start(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(px, py);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("glDrawPixels example");

	glutDisplayFunc(drawFrame);
	glutIdleFunc(triggerReDraw);

	glutMouseFunc(mouseDepressed);
	glutMotionFunc(mouseMovingDepressed);
	//glutKeyboardFunc(KeyboardDepressed);

	glutMainLoop();
}
