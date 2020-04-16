#include <stdio.h>
#include "stdafx.h"


void presentationWall(GLuint texture) {
	
	glTranslatef(0, 0, 5);		//scaling and translating so it fits onto rooms
	glScalef(5.0f, 5.0f, 5.0f);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	//( width, height, depth)
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.75f, -0.42f, -0.99f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.75f, -0.42f, -0.99f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.75f, 0.42f, -0.99f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.75f, 0.42f, -0.99f);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glTranslatef(1.5, 0, 0); //translation to next presentation slide position
	glScalef(0.2f, 0.2f, 0.2f);//scaling and translating back
	glTranslatef(0, 0, -5);
}

//ich wäre farbig wenn etwas von meister talents tentakeln auf mich abfroht
void plainWall(int a, int b, int c) {	//wall in different color(a,b,c), if needed for anyp purposes

	glBegin(GL_QUADS);
	
	glColor3f(a, b, c);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.75f, -0.42f, -0.99f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.75f, -0.42f, -0.99f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.75f, 0.42f, -0.99f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.75f, 0.42f, -0.99f);
	
	glEnd();

}


void roomDoor() {	//wall with door
	glRotatef(90, 0, 2, 0);	//rotating advances to next wall when pieced together

	glBegin(GL_QUADS);
	// left side
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(4.0f, 0.0f); glVertex3f(-0.2f, -1.0f, 1.0f);
	glTexCoord2f(4.0f, 10.0f); glVertex3f(-0.2f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	
	//above door
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.2f, -0.2f, 1.0f);
	glTexCoord2f(2.0f, 0.0f); glVertex3f(0.2f, -0.2f, 1.0f);
	glTexCoord2f(2.0f, 6.0f); glVertex3f(0.2f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 6.0f); glVertex3f(-0.2f, 1.0f, 1.0f);
	
	//right side
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, -1.0f, 1.0f);
	glTexCoord2f(4.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(4.0f, 10.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(0.2f, 1.0f, 1.0f);
	
	glEnd();
}

void roomWall() {	//plain wall
	glRotatef(90, 0, 2, 0);	//rotating advances to next wall when pieced together

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(10.0f, 10.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
}

void roomCeiling() {	//ceiling

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(10.0f, 10.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
}
void roomFloor(){	//floor 
	glBegin(GL_QUADS);

	// floor
	glTexCoord2f(10.0f, 10.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
}


//combining walls, floors and ceiling to room
//no wall = 0; wall with door = 1; plain wall = 2;
//wall order: right, front, left, back
//textureA = floor, textureB= walls and ceiling
void theRoom(int aDoor, int bDoor, int cDoor, int dDoor, GLuint textureA, GLuint textureB) {	
	
	glTranslatef(0, 5, 9);		//translating height and depth for correct position
	glScalef(10.0f, 10.0f, 10.0f);	//scaling rooms for more size
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, textureA);

	roomFloor();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, textureB);
	roomCeiling();
	//right wall
	if (aDoor == 1) {
		roomDoor();
	} 
	else if(aDoor == 2){
		roomWall(); 
	}
	else {
		glRotatef(90, 0, 2, 0);	//rotating advances to next wall when pieced together
	}
	//front wall
	if (bDoor == 1) {
		roomDoor();
	}
	else if (bDoor == 2) {
		roomWall();
	}
	else {
		glRotatef(90, 0, 2, 0);
	}
	//left wall
	if (cDoor == 1) {
		roomDoor();
	}
	else if (cDoor == 2) {
		roomWall();
	}
	else {
		glRotatef(90, 0, 2, 0);
	}
	//back wall
	if (dDoor == 1) {
		roomDoor();
	}
	else if (dDoor == 2) {
		roomWall();
	}
	else {
		glRotatef(90, 0, 2, 0);
	}
	glDisable(GL_TEXTURE_2D);

	glScalef(0.1f, 0.1f, 0.1f);	//scaling and translating back
	glTranslatef(0, -5, -9);
	
}


// many rooms pieced together for presentation
void presentationRoom(int numberOfRooms, GLuint textureA, GLuint textureB) {
	
	//first room
	theRoom(0, 2, 1, 2, textureA, textureB);
	glTranslatef(20.0f, 0, 0);	//dont forget the room scaling...

	//rooms inbetween
	for(int i=1; i<=(numberOfRooms-2); i++){
		theRoom(0, 2, 0, 2, textureA, textureB);
		glTranslatef(20.0f, 0, 0);	//dont forget the room scaling...
	}

	//last room
	theRoom(1, 2, 0, 2, textureA, textureB);

}