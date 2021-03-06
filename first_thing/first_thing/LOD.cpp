#include "LOD.hpp"


void drawTree(double dist1, double dist2, double dist3) {


	//sorting distances
	double dist[3] = { dist1, dist2, dist3 }; 
	double swap = 0;
	int n = 3;

	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n - j; i++)
		{
			if (dist[i] < dist[i + 1])
			{
				swap = dist[i];
				dist[i] = dist[i + 1];
				dist[i + 1] = swap;
			}
		}

	}

		printf("Sorted list in descending order:\n");
		for (int i = 0; i < 3; i++)
		{
			printf("%f\n", dist[i]);
		}


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	for (int i = 0; i < 3; i++) {

		if (dist[i] == dist1) {
			glPushMatrix();
			glColor4f(1.0f, 0.0f, 0.0f, 0.3f); // red triangle
			if (dist1 > 25) {
				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 0.0f, -4.0f);
				glVertex3f(0.0f, 0.0f, 4.0f);
				glVertex3f(0.0f, 8.0f, 0.0f);
				glEnd();
			}
			else {
				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 0.0f, -4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, -2.0f);
				glEnd();

				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 0.0f, 4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, 2.0f);
				glEnd();

				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 4.0f, -2.0f); glVertex3f(0.0f, 4.0f, 2.0f); glVertex3f(0.0f, 8.0f, 0.0f);
				glEnd();
			}
		}


		if (dist[i] == dist2) {
			glPushMatrix();
			glColor4f(0.0f, 1.0f, 0.0f, 0.3f); // green triangle
			glTranslatef(-1.0f, 0.0f, -1.0f);
			if (dist2 > 25) {
				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 0.0f, -4.0f);
				glVertex3f(0.0f, 0.0f, 4.0f);
				glVertex3f(0.0f, 8.0f, 0.0f);
				glEnd();
			}
			else {
				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 0.0f, -4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, -2.0f);
				glEnd();

				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 0.0f, 4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, 2.0f);
				glEnd();

				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 4.0f, -2.0f); glVertex3f(0.0f, 4.0f, 2.0f); glVertex3f(0.0f, 8.0f, 0.0f);
				glEnd();
			}
			glPopMatrix();
		}

		if(dist[i] == dist3){
			glPushMatrix();
			glColor4f(0.0f, 0.0f, 1.0f, 0.3f); //blue triangle
			glTranslatef(-3.0f, 0.0f, 1.0f);
			if (dist3 > 25) {
				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 0.0f, -4.0f);
				glVertex3f(0.0f, 0.0f, 4.0f);
				glVertex3f(0.0f, 8.0f, 0.0f);
				glEnd();
			}
			else {
				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 0.0f, -4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, -2.0f);
				glEnd();

				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 0.0f, 4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, 2.0f);
				glEnd();

				glBegin(GL_TRIANGLES);
				glVertex3f(0.0f, 4.0f, -2.0f); glVertex3f(0.0f, 4.0f, 2.0f); glVertex3f(0.0f, 8.0f, 0.0f);
				glEnd();
			}
			glPopMatrix();
		}
	

	}

	glDisable(GL_BLEND);

	glPopMatrix();
}


void fractalTree(double dist) {

	glColor4f(1.0f, 0.0f, 0.0f, 0.3f); // red triangle

	if(dist > 60 ){
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f);
	glVertex3f(0.0f, 0.0f, 4.0f);
	glVertex3f(0.0f, 8.0f, 0.0f);
	glEnd();
	}else if(dist > 40) {
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, -4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, -2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 0.0f, 4.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.0f, 4.0f, -2.0f); glVertex3f(0.0f, 4.0f, 2.0f); glVertex3f(0.0f, 8.0f, 0.0f);
	glEnd();

	}else if(dist > 20){
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
	else {


		for(int l = 0; l < 4; l++){
			glPushMatrix();
			for (int k = 0; k < 4 - l; k++) {
				glPushMatrix();
				if(!((k==1) && (l==1))){
				for (int j = 0; j < 2; j++) {
					glPushMatrix();
					for (int i = 0; i < 2 - j; i++) {
						glBegin(GL_TRIANGLES);
						glVertex3f(0.0f, 0.0f, -4.0f); glVertex3f(0.0f, 0.0f, -3.0f); glVertex3f(0.0f, 1.0f, -3.5f);
						glEnd();
						glTranslatef(0.0f, 0.0f, 1.0f);
					}
					glPopMatrix();
					glTranslatef(0.0f, 1.0f, 0.5f);
				}}
				glPopMatrix();
				glTranslatef(0.0f, 0.0f, 2.0f);
			}
			glPopMatrix();
			glTranslatef(0.0f, 2.0f, 1.0f);
		}
		
	}
}

double getDistance(double pos1x, double pos1y, double pos1z, double pos2x, double pos2y, double pos2z ) {
	return sqrt(pow(pos2x - pos1x, 2) + pow(pos2y - pos1y, 2) + pow(pos2z - pos1z, 2));
}