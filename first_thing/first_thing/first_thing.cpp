#include "stdafx.h"
#include "second_thing.hpp"
#include "redraw_glitch.hpp"
#include "art.hpp"
#include "funny_glitch.hpp"
#include "light.hpp"
#include "LOD.hpp"
#include <cstring>

int window;

GLuint texture[24];

//position of player
double posX = 0;
double posY = 0;
double posZ = -5;

//variable indicading keys being pressed
bool wPressed = 0;
bool aPressed = 0;
bool sPressed = 0;
bool dPressed = 0;

GLfloat angle_y = 0;  /* angle of spin around y axis of scene, in degrees */	//for turning
GLfloat angle_x = 0;  /* angle of spin around x axis  of scene, in degrees */

//save mouse position to calculate difference between this game tick and the last
float mouseX = 0;
float mouseY = 0;

//mipmap
bool mipmap = false;

void reportGLError(const char * msg)
{
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		fprintf(stderr, "OpenGL Error: %s %s\n", msg, errString);
	}
	return;
}

void resize(int width, int height)
{
	// prevent division by zero
	if (height == 0) { height = 1; }

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void specialKeyPressed(int key, int x, int y)
{

	switch (key) {

	case GLUT_KEY_RIGHT:     /* <next slide> */
		posX -= SLIDE_SIZE;
		break;
	case GLUT_KEY_DOWN:		/*down movement*/
		posY += 0.2f;
		break;
	case GLUT_KEY_LEFT:     /* <previous slide> */
		posX += SLIDE_SIZE;
		break;
	case GLUT_KEY_UP:		/*up movement*/
		posY -= 0.2f;
		break;
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:	//ESC key
		glutDestroyWindow(window);
		exit(0);			     //exit program
		break;
	case 'w':	//Move camera with WASD
		wPressed = 1;
		break;
	case 'a':
		aPressed = 1;
		break;
	case 's':
		sPressed = 1;
		break;
	case 'd':
		dPressed = 1;
		break;
	case 32:	//SPACE key
		posX -= SLIDE_SIZE;     /* <next slide> */
		glutPostRedisplay();
		break;
	case 13:	//ENTER key
		posX -= SLIDE_SIZE;     /* <next slide> */
		glutPostRedisplay();
		break;
	case 'm':
		mipmap = !mipmap;		//activate mipmap
		break;
	default:
		break;
	}
}

void keyReleased(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':		//set <key>Pressed variables back to 0 on key release
		wPressed = 0;
		break;
	case 'a':
		aPressed = 0;
		break;
	case 's':
		sPressed = 0;
		break;
	case 'd':
		dPressed = 0;
		break;
	default:
		break;
	}
}

void display()
{
	int mipped;

	if (mipmap) {
		mipped = 12;
	}
	else {
		mipped = 0;
	}


	if (checkIfInRedrawGlitchRoom(posX, posZ)) {	//specific behaviour for redrawGlitch
		glClear(GL_DEPTH_BUFFER_BIT);
		glDepthMask(GL_TRUE);
	}
	else if (checkIfInFunnyGlitchRoom(posX, posZ)) {//specific behaviour for funnyGlitch
		glClear(GL_DEPTH_BUFFER_BIT);
		glDepthMask(GL_FALSE);
	}
	else {		//normal behaviour for colour buffer and depth mask
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthMask(GL_TRUE);
	}

	glLoadIdentity();

	//calculate custom y value for gluLookAt
	GLfloat cur_x = angle_x;
	float calced_sin_x = 0;
	//increase value beyond 1 (max for sin(angle_x) )
	while (cur_x > 90.0) {
		calced_sin_x += 1;
		cur_x -= 90;
	}
	while (cur_x < -90.0) {
		calced_sin_x -= 1;
		cur_x += 90;
	}
	calced_sin_x += sinf(RAD(cur_x));
	//square value to get smoother look movement (otherwise it gets slower the further you get from angle_x = 0)
	if (calced_sin_x > 0) {
		calced_sin_x *= calced_sin_x;
	}
	else {
		calced_sin_x *= -calced_sin_x;
	}

	gluLookAt(-sinf(RAD(angle_y)), calced_sin_x, cosf(RAD(angle_y)),
		0., 0., 0.,
		0., 1., 0.);

	//moves view back into the center (without this the camera moves down when you look up and vice versa)
	glTranslatef(-sinf(RAD(angle_y)), calced_sin_x, cosf(RAD(angle_y)));


	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texture[0 + mipped]);

	glTranslatef(posX, posY, posZ);

	// because 2 different textures per room, we need to hand over textures, first one floor, second one ceiling + walls

	glPushMatrix();		//big room with number of rooms
	presentationRoom(3, texture[2 + mipped], texture[1 + mipped]);
	glPopMatrix();

	glPushMatrix();		//rooms for nico
	glTranslatef(20.0f, 0, 20.0f);		//sun system room
	theRoom(0, 0, 0, 1, texture[2 + mipped], texture[1 + mipped]);
	glTranslatef(0, 0, 20.0f);		//weird house room
	theRoom(2, 0, 2, 2, texture[2 + mipped], texture[1 + mipped]);
	glPopMatrix();


	glPushMatrix();		//nicos cool cube room 
	glTranslatef(60.0f, 0, 0);
	theRoom(2, 2, 0, 1, texture[2 + mipped], texture[1 + mipped]);
	glPopMatrix();

	glPushMatrix();		//presentation slides in presentation
	for (int i = 0; i < 6; i++) {
		presentationWall(texture[i + 3 + mipped]);
	}
	glPopMatrix();

	glPushMatrix();		//nicos sun system
	glTranslatef(10, 0, -10);
	glScalef(9.99f, 9.99f, 9.99f);
	glTranslatef(6, 0, 0);
	drawRedrawGlitch();
	glPopMatrix();

	glPushMatrix();		//nicos cool cube
	glTranslatef(85.0f, 0, 0);
	glScalef(5, 5, 5);
	glTranslatef(-5, 0, 2);
	// Multi-colored side - FRONT
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	// Black side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
	glPopMatrix();


	glPushMatrix();			//lleongs room with cool picture(s)
	glTranslatef(60.0f, 0, 20.0f);
	theRoom(2, 0, 1, 2, texture[2 + mipped], texture[1 + mipped]);

	makeArt(texture[9 + mipped], texture[10 + mipped], texture[11 + mipped]);

	glPopMatrix();

	drawFunnyGlitch();		//nicos weird house

	glPushMatrix();		//lleongs room with egg
	glTranslatef(40.0f, 0, 20.0f);		//position relevant
	theRoom(0, 0, 1, 2, texture[2 + mipped], texture[1 + mipped]);

	illuminate();
	glPopMatrix();


	//big room for lod and transparency
	glPushMatrix();		
	glTranslatef(-20.0f, 0, 0);		
	theRoom(0, 0, 0, 0, texture[2 + mipped], texture[1 + mipped]);
	glTranslatef(0, 0, -20.0f);
	theRoom(2, 2, 0, 0, texture[2 + mipped], texture[1 + mipped]);
	glTranslatef(0, 0, 40.0f);
	theRoom(2, 0, 0, 2, texture[2 + mipped], texture[1 + mipped]);
	glTranslatef(-20.0f, 0, -20.0f);
	theRoom(0, 0, 0, 0, texture[2 + mipped], texture[1 + mipped]);
	glTranslatef(0, 0, -20.0f);
	theRoom(0, 2, 0, 0, texture[2 + mipped], texture[1 + mipped]);
	glTranslatef(0, 0, 40.0f);
	theRoom(0, 0, 0, 2, texture[2 + mipped], texture[1 + mipped]);
	glTranslatef(-20.0f, 0, -20.0f);
	theRoom(0, 0, 2, 0, texture[2 + mipped], texture[1 + mipped]);
	glTranslatef(0, 0, -20.0f);
	theRoom(0, 2, 2, 0, texture[2 + mipped], texture[1 + mipped]);
	glTranslatef(0, 0, 40.0f);
	theRoom(0, 0, 2, 2, texture[2 + mipped], texture[1 + mipped]);
	glPopMatrix();

	

	//LOD triangle
	//position for LOD triangles
	double x4, y4, z4;
	x4 = -68;
	y4 = -5;
	z4 = -10;
	double dist = getDistance(x4, y4, z4, -posX, -posY, -posZ);
	//printf("%f ", dist); check distance
	glPushMatrix();
	glTranslatef(x4, y4, z4);
	fractalTree(dist);
	glPopMatrix();
	
	//Transparent Triangles
	//positions for transparent triangles
	double x1, y1, z1, x2, y2, z2, x3, y3, z3;
	x1 = -45;
	y1 = -3;
	z1 = 10;
	x2 = x1 - 1;
	y2 = y1;
	z2 = z1 - 1;
	x3 = x1 -3;
	y3 = y1;
	z3 = z1 + 1;
	double dist1 = getDistance(x1, y1, z1, -posX, -posY, -posZ);
	double dist2 = getDistance(x2, y2, z2, -posX, -posY, -posZ);
	double dist3 = getDistance(x3, y3, z3, -posX, -posY, -posZ);
	glPushMatrix();
	glTranslatef(x1, -5, z1);
	drawTree(dist1, dist2, dist3);
	glPopMatrix();


	glutSwapBuffers();
}

void texCreator(const char constName[255], GLsizei* w, GLsizei* h, int* mode, int index, bool mapMipped) {	//function for loading an image into texture[index]
	tgaInfo* info = 0;

	char name[255];
	strcpy(name, constName);

	info = tgaLoad(name);	//filename

	if (info->status != TGA_OK) {
		fprintf(stderr, "error loading texture image: %d\n", info->status);
		return;
	}

	*mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture[index]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Upload the texture bitmap. 
	*w = info->width;
	*h = info->height;

	reportGLError("before uploading texture");
	GLint format = (*mode == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, *w, *h, 0, format,
		GL_UNSIGNED_BYTE, info->imageData);
	reportGLError("after uploading texture");

	if (mapMipped) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	tgaDestroy(info);
}

void init(int width, int height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	resize(width, height);

	GLsizei w, h;
	int mode;

	//prepare for 24 images
	glGenTextures(24, texture);

	//load images
	texCreator("crate.tga", &w, &h, &mode, 0, false);
	texCreator("wallBit.tga", &w, &h, &mode, 1, false);
	texCreator("floorTiles.tga", &w, &h, &mode, 2, false);
	texCreator("Folie1.tga", &w, &h, &mode, 3, false);
	texCreator("Folie2.tga", &w, &h, &mode, 4, false);
	texCreator("Folie3.tga", &w, &h, &mode, 5, false);
	texCreator("Folie4.tga", &w, &h, &mode, 6, false);
	texCreator("Folie5.tga", &w, &h, &mode, 7, false);
	texCreator("Folie6.tga", &w, &h, &mode, 8, false);
	texCreator("painting1.tga", &w, &h, &mode, 9, false);
	texCreator("painting2.tga", &w, &h, &mode, 10, false);
	texCreator("painting3.tga", &w, &h, &mode, 11, false);

	//with mipmap
	texCreator("crate.tga", &w, &h, &mode, 12, true);
	texCreator("wallBit.tga", &w, &h, &mode, 13, true);
	texCreator("floorTiles.tga", &w, &h, &mode, 14, true);
	texCreator("Folie1.tga", &w, &h, &mode, 15, true);
	texCreator("Folie2.tga", &w, &h, &mode, 16, true);
	texCreator("Folie3.tga", &w, &h, &mode, 17, true);
	texCreator("Folie4.tga", &w, &h, &mode, 18, true);
	texCreator("Folie5.tga", &w, &h, &mode, 19, true);
	texCreator("Folie6.tga", &w, &h, &mode, 20, true);
	texCreator("painting1.tga", &w, &h, &mode, 21, true);
	texCreator("painting2.tga", &w, &h, &mode, 22, true);
	texCreator("painting3.tga", &w, &h, &mode, 23, true);
}

void calcMovement(float speed) {
	float vecX = 0.0f;
	float vecY = 0.0f;

	//if key is pressed move <speed> in direction or speed/squrt(2) if moving diagonally 
	if (wPressed == 1) {
		if (aPressed || dPressed) {
			vecY += speed / SQRT2;
		}
		else {
			vecY += speed;
		}
	}
	if (aPressed == 1) {
		if (wPressed || sPressed) {
			vecX += speed / SQRT2;
		}
		else {
			vecX += speed;
		}
	}
	if (sPressed == 1) {
		if (aPressed || dPressed) {
			vecY -= speed / SQRT2;
		}
		else {
			vecY -= speed;
		}

	}
	if (dPressed == 1) {
		if (wPressed || sPressed) {
			vecX -= speed / SQRT2;
		}
		else {
			vecX -= speed;
		}
	}

	//multiply movement vector with rotation matrix to move relative to direction the camera is looking in
	posX += (cosf(RAD(angle_y)) * vecX) + (-sinf(RAD(angle_y)) * vecY);
	posZ += (sinf(RAD(angle_y)) * vecX) + (cosf(RAD(angle_y)) * vecY);
}

void timer(int value)
{
	calcMovement(0.3f);	//calculate movement based on which buttons are being pressed
	glutPostRedisplay();	//redisplay each time step for stable animation speed and frame rate
	glutTimerFunc(15, timer, 1);
}


void mouseMotion(int x, int y) {
	int max_look_up = 180;

	//difference between last tick and this tick
	int diffx = x - mouseX;
	int diffy = y - mouseY;

	/* calculate new modelview matrix values */
	angle_y = angle_y + diffx;
	angle_x = angle_x + diffy;
	if (angle_x > max_look_up) angle_x = max_look_up;
	else if (angle_x < -max_look_up) angle_x = -max_look_up;
	if (angle_y > 360.0) angle_y -= 360.0;
	else if (angle_y < -360.0) angle_y += 360.0;

	//set values for next tick
	mouseX = x;
	mouseY = y;

	//ensure mouse stays in window and enables endless mouse movement in every direction
	if ((mouseX == 0) || (GLUT_WINDOW_WIDTH - mouseX) == 0 || (mouseY == 0) || (GLUT_WINDOW_HEIGHT - mouseY) == 0) {
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
		mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	}
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("Glitch Museum");
	GLenum err = glewInit();
	if (GLEW_OK != err) //glew error
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutKeyboardUpFunc(&keyReleased);
	glutSpecialFunc(&specialKeyPressed);
	init(640, 480);
	glutTimerFunc(15, timer, 1);
	glutPassiveMotionFunc(mouseMotion);
	glutMotionFunc(mouseMotion);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(952, 505);
	glutFullScreen();
	glutMainLoop();
	return 0;
}