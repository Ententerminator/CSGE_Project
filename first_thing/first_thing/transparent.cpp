#include "transparent.hpp"

float hours = 0.0;
float daytime = 0.0;
float incr = 20.00;


void drawSunSystem() {
	hours += incr;
	daytime += incr / 24.0;
	hours = hours - ((int)(hours / 24)) * 24;
	daytime = daytime - ((int)(daytime / 365)) * 365;

	glTranslatef(-6.0, 0.0, 4.0);
	glScalef(1.0, 1.0, 1.0);
	//glRotatef(360 * daytime / 365.0, 0.0, 1.0, 0.0); //sun around itself

	// ecliptic rotation
	glRotatef(15.0, 1.0, 0.0, 0.0);

	// sun
	glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
	glutSolidSphere(1.0, 15, 15);

	// earth
	// position around the sun
	//glRotatef(360.0 * daytime / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(4.0, 0.0, 0.0);

	glPushMatrix();
	// rotate the earth on its axis
	//glRotatef(360.0 * hours / 24.0, 0.0, 1.0, 0.0);
	glColor4f(0.3f, 0.7f, 0.7f, 0.3f);
	glutSolidSphere(0.4, 10, 10);
	glPopMatrix();

	// moon
	glRotatef(360.0 * 4 * daytime / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(0.7f, 0.0f, 0.0f);
	glColor4f(0.7f, 0.3f, 0.7f, 0.3f);
	glutSolidSphere(0.1f, 10, 10);
}

float playerDistance() {
	//do something
	return 0.0f;
}