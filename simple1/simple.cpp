// simple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "C:\GLFiles\include\GL\glaux.h"
static GLfloat spin = 0.0;
void CALLBACK  display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glRectf(-25.0, -25.0, 25.0, 25.0);
	glPopMatrix();
	glFlush();
	auxSwapBuffers();
}
void CALLBACK  spinDisplay(void)
{
	spin = spin + 2.0;
	if (spin > 360.0)
		spin = spin - 360.0;
	display();
}

void CALLBACK startIdleFunc(AUX_EVENTREC *event)
{
	auxIdleFunc(spinDisplay);
}
void CALLBACK  stopIdleFunc(AUX_EVENTREC *event)
{
	auxIdleFunc(0);
}

void myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 1.0);
	glShadeModel(GL_FLAT);
}
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-50.0, 50.0, -50.0*(GLfloat)h / (GLfloat)w, 50.0*(GLfloat)h / (GLfloat)w, -1.0, 1.0);
	else
		glOrtho(-50.0*(GLfloat)w / (GLfloat)h, 50.0*(GLfloat)w / (GLfloat)h, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int _tmain(int argc, _TCHAR* argv[])
{
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGBA);
	auxInitPosition(0, 0, 500, 500);
	auxInitWindow(argv[0]);
	myinit();
	auxReshapeFunc(myReshape);
	auxIdleFunc(spinDisplay);
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, startIdleFunc);
	auxMouseFunc(AUX_MIDDLEBUTTON, AUX_MOUSEDOWN, stopIdleFunc);
	auxMainLoop(display);

	return 0;
}

