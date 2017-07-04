#include <windows.h> 
#include "freeglut.h"
#include <math.h> 
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

double xVector = M_PI_2, yVector = 0;
double distance = 30;
double positionOnX = 0;
double positionOnY = 0;
double positionOnZ = distance;

float fovy = 90.0, aspect = 1.0, near_ = 0.1, far_ = 45.0;

//kula koloru czerwonego o œrodku w punkcie (0, 2, 0) i promieniu 2
void drawSphere()
{
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 2.0, 0.0);
	glutSolidSphere(2, 111, 111);
	glPopMatrix();
}

void drawCellOfTable()
{
	glBegin(GL_QUADS);
	glVertex3f(12.0, 3.0, 0.0);
	glVertex3f(12.0, -3.0, 0.0);
	glVertex3f(-10.0, -3.0, 0.0);
	glVertex3f(-10.0, 3.0, 0.0);
	glEnd();
}
void drawFrontWallOfTable()
{
	glBegin(GL_QUADS);
	glVertex3f(12.0, 0.0, 3.0);
	glVertex3f(12.0, -4.0, 3.0);
	glVertex3f(-10.0, -4.0, 3.0);
	glVertex3f(-10.0, 0.0, 3.0);
	glEnd();
}
void drawSideWallOfTable()
{
	glBegin(GL_QUADS);
	glVertex3f(3.0, 0.0, 0.0);
	glVertex3f(3.0, -4.0, 0.0);
	glVertex3f(-3.0, -4.0, 0.0);
	glVertex3f(-3.0, 0.0, 0.0);
	glEnd();
}
void setCellOfTable()
{
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	//obrót wokó³ osi X o 90 stopni
	glRotatef(90.0, 1.0, 0.0, 0.0);
	drawCellOfTable();
	glPopMatrix();
}
void setFloorOfTable()
{
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	//przesuniêcie wzd³u¿ osi Y o -4.0
	glTranslatef(0.0, -4.0, 0.0);
	//obrót wokó³ osi X o 90 stopni
	glRotatef(90.0, 1.0, 0.0, 0.0);
	drawCellOfTable();
	glPopMatrix();
}
void setFrontOfTable()
{
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	drawFrontWallOfTable();
	glPopMatrix();
}
void setBackOfTable()
{
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	//przesuniêcie wzd³u¿ osi Z o -6.0
	glTranslatef(0.0, 0.0, -3.0);
	drawFrontWallOfTable();
	glPopMatrix();
}
void setLeftSideOfTable()
{
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	//przesuniêcie wzd³u¿ osi X o -10.0
	glTranslatef(-10.0, 0.0, 0.0);
	//obrót wokó³ osi Y o 90 stopni
	glRotatef(90.0, 0.0, 1.0, 0.0);
	drawSideWallOfTable();
	glPopMatrix();
}
void setRightSideOfTable()
{
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	//przesuniêcie wzd³u¿ osi X o +12.0
	glTranslatef(12.0, 0.0, 0.0);
	//obrót wokó³ osi Y o 90 stopni
	glRotatef(90.0, 0.0, 1.0, 0.0);
	drawSideWallOfTable();
	glPopMatrix();
}
void drawTable()
{
	setCellOfTable();
	setFloorOfTable();
	setFrontOfTable();
	setBackOfTable();
	setLeftSideOfTable();
	setRightSideOfTable();
}
//front liter - równoleg³obok
void drawFrontParallelogram()
{
	glBegin(GL_QUADS);
	glVertex3f(4.0, 12.0, 2.0);
	glVertex3f(1.0, 0.0, 2.0);
	glVertex3f(-1.0, 0.0, 2.0);
	glVertex3f(2.0, 12.0, 2.0);
	glEnd();
}
//front liter - prostok¹t
void drawFrontRectangle()
{
	glBegin(GL_QUADS);
	glVertex3f(1.0, 12.0, 2.0);
	glVertex3f(1.0, 0.0, 2.0);
	glVertex3f(-1.0, 0.0, 2.0);
	glVertex3f(-1.0, 12.0, 2.0);
	glEnd();
}
void drawVerticalSideOfM()
{
	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(2.0, 12.0, 2.0);
	glVertex3f(2.0, 0.0, 2.0);
	glVertex3f(-2.0, 0.0, 2.0);
	glVertex3f(-2.0, 12.0, 2.0);
	glEnd();
	glPopMatrix();
}
void drawLeftSlopedSideOfM()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-2.0, 0.0, 2.0);
	glVertex3f(-2.0, 0.0, -2.0);
	glVertex3f(-5.0, 12.0, -2.0);
	glVertex3f(-5.0, 12.0, 2.0);
	glEnd();
	glPopMatrix();
}
void drawRightSlopedSideOfM()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-10.0, 0.0, 2.0);
	glVertex3f(-10.0, 0.0, -2.0);
	glVertex3f(-7.0, 12.0, -2.0);
	glVertex3f(-7.0, 12.0, 2.0);
	glEnd();
	glPopMatrix();
}
void drawfrontOfA()
{
	glPushMatrix();
	glTranslatef(-9.0, 0.0, 0.0);
	drawFrontParallelogram();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.0, 0.0, 4.0);
	glRotatef(180.0, 0.0, 1.0, 0.0);
	drawFrontParallelogram();
	glPopMatrix();
}
void drawBackOfA()
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, -4.0);
	drawfrontOfA();
	glPopMatrix();
}
void drawSidesOfA()
{
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	drawLeftSlopedSideOfM();
	glTranslatef(-2.0, 0.0, 0.0);
	drawLeftSlopedSideOfM();
	glPopMatrix();
	glPushMatrix();
	drawRightSlopedSideOfM();
	glTranslatef(2.0, 0.0, 0.0);
	drawRightSlopedSideOfM();
	glPopMatrix();
}
void drawFrontParallelogramOfM()
{
	glPushMatrix();
	glTranslatef(7.0, 0.0, 0.0);
	drawFrontParallelogram();
	glPopMatrix();
	glPushMatrix();
	//przesuniêcie wzd³u¿ osi X o 7.0 i o 4 na osi Z
	glTranslatef(7.0, 0.0, 4.0);
	//obrót wokó³ osi Y o 180 stopni
	glRotatef(180.0, 0.0, 1.0, 0.0);
	drawFrontParallelogram();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(3.0, 0.0, 0.0);
	drawFrontRectangle();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(11.0, 0.0, 0.0);
	drawFrontRectangle();
	glPopMatrix();
}
void drawFrontOfBar()
{
	glBegin(GL_QUADS);
	glVertex3f(2.0, 0.0, 2.0);
	glVertex3f(2.0, 2.0, 2.0);
	glVertex3f(-2.0, 2.0, 2.0);
	glVertex3f(-2.0, 0.0, 2.0);
	glEnd();
}
void drawTopOfBar()
{
	glBegin(GL_QUADS);
	glVertex3f(2.0, 0.0, 2.0);
	glVertex3f(2.0, 4.0, 2.0);
	glVertex3f(-2.0, 4.0, 2.0);
	glVertex3f(-2.0, 0.0, 2.0);
	glEnd();
}
void drawHorizontalBar()
{
	//przód belki
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(-6.0, 2.0, 0.0);
	drawFrontOfBar();
	glPopMatrix();
	//ty³ belki
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(-6.0, 2.0, -4.0);
	drawFrontOfBar();
	glPopMatrix();
	//góra belki
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(-6.0, 6.0, -2.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	drawTopOfBar();
	glPopMatrix();
	//dó³ belki
	glPushMatrix();
	glTranslatef(-6.0, 4.0, -2.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	drawTopOfBar();
	glPopMatrix();
}

void drawTopOfLetter()
{
	glBegin(GL_QUADS);
	glVertex3f(1.0, 0.0, 2.0);
	glVertex3f(1.0, 4.0, 2.0);
	glVertex3f(-1.0, 4.0, 2.0);
	glVertex3f(-1.0, 0.0, 2.0);
	glEnd();
}

void drawTopOfA()
{
	glPushMatrix();
	glTranslatef(-6.0, 14.0, -2.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	drawTopOfLetter();
	glPopMatrix();
}
void drawFrontOfM()
{
	glPushMatrix();
	drawFrontParallelogramOfM();
	glPopMatrix();
}
void drawBackOfM()
{
	glPushMatrix();
	glTranslatef(0.0, 0.0, -4.0);
	drawFrontParallelogramOfM();
	glPopMatrix();
}
void drawAllSidesOfM()
{
	//literka M pionowe boki
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	drawVerticalSideOfM();
	glTranslatef(2.0, 0.0, 0.0);
	drawVerticalSideOfM();
	glTranslatef(6.0, 0.0, 0.0);
	drawVerticalSideOfM();
	glTranslatef(2.0, 0.0, 0.0);
	drawVerticalSideOfM();
	glPopMatrix();
	//literka M pochylone boki
	glPushMatrix();
	glTranslatef(8.0, 0.0, 0.0);
	drawLeftSlopedSideOfM();
	glTranslatef(2.0, 0.0, 0.0);
	drawLeftSlopedSideOfM();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(16.0, 0.0, 0.0);
	drawRightSlopedSideOfM();
	glTranslatef(2.0, 0.0, 0.0);
	drawRightSlopedSideOfM();
	glPopMatrix();
}
void drawLeftTopOfM()
{
	glPushMatrix();
	glTranslatef(4.0, 14.0, -2.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	drawTopOfLetter();
	glTranslatef(-1.0, 0.0, 0.0);
	drawTopOfLetter();
	glPopMatrix();
}
void drawTopOfM()
{
	glPushMatrix();
	drawLeftTopOfM();
	glTranslatef(7.0, 0.0, 0.0);
	drawLeftTopOfM();
	glPopMatrix();
}
void drawA()
{
	glColor3f(1.0, 1.0, 0.0);
	drawfrontOfA();
	glColor3f(1.0, 0.0, 0.0);
	drawBackOfA();
	drawSidesOfA();
	drawHorizontalBar();
	drawTopOfA();
}

void drawM()
{
	glColor3f(1.0, 1.0, 0.0);
	drawFrontOfM();
	glColor3f(1.0, 0.0, 0.0);
	drawBackOfM();
	drawAllSidesOfM();
	drawTopOfM();
}
void setpositionOnXYZ()
{
	positionOnX = distance * cos(xVector) * cos(yVector);
	positionOnY = distance * sin(yVector);
	positionOnZ = distance * sin(xVector) * cos(yVector);
}
void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//"czyszczenie" t³a okan i bufora g³êbokosci
	glEnable(GL_DEPTH_TEST);//w³¹cznie algorytmu zas³aniania
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, near_, far_); //bry³a widzenia perspektywicznego
	gluLookAt(positionOnX, positionOnY, positionOnZ, 0, 0, 0, 0, 1, 0);//obserwator - pozycja pocz¹tkowa (0,0,30), „wzrok” skierowany na punkt (0,0,0),
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	setpositionOnXYZ();

	drawSphere();
	drawTable();
	drawA();
	drawM();

	glFlush();
}
void useKeyboard(unsigned char key, int x, int y)
{
	if (key == '-')
	{
		distance += 2;
	}
	if (key == '+')
	{
		distance -= 2;
	}

	glutPostRedisplay();
}

void useSpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT: xVector += 0.1;
		break;
	case GLUT_KEY_DOWN: yVector -= 0.1;
		break;
	case GLUT_KEY_RIGHT: xVector -= 0.1;
		break;
	case GLUT_KEY_UP: yVector += 0.1;
		break;
	};
	glutPostRedisplay();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Aleksandra Mak - inicja³y");
	glutDisplayFunc(display);
	glutKeyboardFunc(useKeyboard);
	glutSpecialFunc(useSpecialKeys);
	glutMainLoop();
}