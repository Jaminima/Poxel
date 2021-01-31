#pragma once
#include "GL/glut.h"
#include "GL/freeglut.h"

#include "Color.h"
#include "Const.h"
#include "Voxler.h"


	bool BufferSwitch = false;
	Color* rgbBuffer = static_cast<Color*>(malloc(px * py * 2 * sizeof(Color)));

	void drawFrame() {
		glDrawPixels(px, py, GL_RGBA, GL_UNSIGNED_INT, &rgbBuffer[!BufferSwitch * px * py]);
		glutSwapBuffers();
	}

	void triggerReDraw()
	{
		array_view<Color, 3> rgbView(2, py, px, rgbBuffer);

		processTick(rgbView, BufferSwitch);

		rgbView.synchronize();

		glutPostRedisplay();

		BufferSwitch = !BufferSwitch;
	}

	void Start(int argc, char** argv) {
		glutInit(&argc, argv);
		glutInitWindowSize(px, py);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
		glutCreateWindow("glDrawPixels example");

		glutDisplayFunc(drawFrame);
		glutIdleFunc(triggerReDraw);

		//glutPassiveMotionFunc(MouseMove);
		//glutKeyboardFunc(KeyboardDepressed);

		glutMainLoop();
	}
