#pragma once
#include "GL/glut.h"
#include "GL/freeglut.h"

#include <iostream>
#include "Color.h"
#include "Const.h"

namespace Window
{
	bool BufferSwitch = false;
	Color* rgbBuffer = new Color[2 * px * py];

	void drawFrame() {
		glDrawPixels(px, py, GL_RGBA, GL_UNSIGNED_INT, &rgbBuffer[!BufferSwitch * px * py]);
		glutSwapBuffers();
	}

	void triggerReDraw()
	{
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

};

