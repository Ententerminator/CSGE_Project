#include "LOD.hpp"


void drawTree(double dist1, double dist2, double dist3) {

	char color[3] = {'r', 'g', 'b'};
	


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//min max suche mit distanzes und dann for schleife
	
	for (int i = 0; i < 3; i++) {

		if (color[i] == 'r') {
			glPushMatrix();
			glColor4f(1.0f, 0.0f, 0.0f, 0.3f); // red triangle
			glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, 0.0f, -4.0f);
			glVertex3f(0.0f, 0.0f, 4.0f);
			glVertex3f(0.0f, 8.0f, 0.0f);
			glEnd();
			glPopMatrix();
		}


		if (color[i] == 'g') {
			glPushMatrix();
			glColor4f(0.0f, 1.0f, 0.0f, 0.3f); // green triangle
			glTranslatef(-1.0f, 0.0f, -1.0f);
			glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, 0.0f, -4.0f);
			glVertex3f(0.0f, 0.0f, 4.0f);
			glVertex3f(0.0f, 8.0f, 0.0f);
			glEnd();
			glPopMatrix();
		}

		if(color[i] == 'b'){
			glPushMatrix();
			glColor4f(0.0f, 0.0f, 1.0f, 0.3f); //blue triangle
			glTranslatef(-3.0f, 0.0f, 1.0f);
			glBegin(GL_TRIANGLES);
			glVertex3f(0.0f, 0.0f, -4.0f);
			glVertex3f(0.0f, 0.0f, 4.0f);
			glVertex3f(0.0f, 8.0f, 0.0f);
			glEnd();
			glPopMatrix();
		}
	

	}

	glDisable(GL_BLEND);

	glPopMatrix();
}


void fractalTree(double dist) {

	glColor4f(1.0f, 0.0f, 0.0f, 0.3f); // red triangle

	if(dist > 40 ){
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f);
	glVertex3f(0.0f, 0.0f, 4.0f);
	glVertex3f(0.0f, 8.0f, 0.0f);
	glEnd();
	}else if(dist > 20) {
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, -2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 4.0f, -2.0f); glVertex3f(0.0f, 4.0f, 2.0f); glVertex3f(0.0f, 8.0f, 0.0f);
	glEnd();

	}else{
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f); glVertex3f(0.0f, 0.0f, -2.0f); glVertex3f(0.0f, 2.0f, -3.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -2.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 2.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 2.0f, -3.0f); glVertex3f(0.0f, 2.0f, -1.0f); glVertex3f(0.0f, 4.0f, -2.0f);
	glEnd();

	glTranslatef(0.0f, 0.0f, 4.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f); glVertex3f(0.0f, 0.0f, -2.0f); glVertex3f(0.0f, 2.0f, -3.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -2.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 2.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 2.0f, -3.0f); glVertex3f(0.0f, 2.0f, -1.0f); glVertex3f(0.0f, 4.0f, -2.0f);
	glEnd();

	glTranslatef(0.0f, 4.0f, -2.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f); glVertex3f(0.0f, 0.0f, -2.0f); glVertex3f(0.0f, 2.0f, -3.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -2.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 2.0f, -1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 2.0f, -3.0f); glVertex3f(0.0f, 2.0f, -1.0f); glVertex3f(0.0f, 4.0f, -2.0f);
	glEnd();


	}
}

double getDistance(double pos1x, double pos1y, double pos1z, double pos2x, double pos2y, double pos2z ) {
	return sqrt(pow(pos2x - pos1x, 2) + pow(pos2y - pos1y, 2) + pow(pos2z - pos1z, 2));
}