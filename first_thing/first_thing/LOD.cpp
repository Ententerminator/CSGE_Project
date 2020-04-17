#include "LOD.hpp"


void drawTree() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//nicht mittelpunkt sondern hochpunkt verwenden
	glColor4f(1.0f, 0.0f, 0.0f, 0.3f); // red triangle

	/*if(getDistance(...)>20){
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glVertex3f(0.0f, 0.0f, 2.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glEnd();
	}
	else if (getDistance(...) > 10) {*/
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f);glVertex3f(0.0f, 0.0f, 0.0f);glVertex3f(0.0f, 4.0f, -2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 4.0f, -2.0f); glVertex3f(0.0f, 4.0f, 2.0f); glVertex3f(0.0f, 8.0f, 0.0f);
	glEnd();

	/*}
	else {
		//more triangles
	}*/


	glColor4f(0.0f, 1.0f, 0.0f, 0.3f); // green triangle

	glTranslatef(-1.0f, 0.0f, -1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f);
	glVertex3f(0.0f, 0.0f, 4.0f);
	glVertex3f(0.0f, 8.0f, 0.0f);
	glEnd();

	glColor4f(0.0f, 0.0f, 1.0f, 0.3f); //blue triangle

	glTranslatef(-2.0f, 0.0f, +2.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f);
	glVertex3f(0.0f, 0.0f, 4.0f);
	glVertex3f(0.0f, 8.0f, 0.0f);
	glEnd();

	glDisable(GL_BLEND);

	glPopMatrix();
}

double getDistance(double pos1x, double pos1y, double pos1z, double pos2x, double pos2y, double pos2z ) {
	return sqrt(pow(pos2x - pos1x, 2) + pow(pos2y - pos1y, 2) + pow(pos2z - pos1z, 2));
}