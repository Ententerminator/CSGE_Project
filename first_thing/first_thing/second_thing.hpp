#pragma once
void presentationWall(GLuint texture);	//presentation slides function
void plainWall(int a, int b, int c);	//wall in different color(a,b,c), if needed for any purposes

void roomDoor();	//wall with door
void roomWall();	//plain wall
void roomFloor();	//floor 
void roomCeiling();	//ceiling

//combining walls, floors and ceiling to room
//no wall = 0; wall with door = 1; plain wall = 2;
//wall order: right, front, left, back
//textureA = floor, textureB= walls and ceiling
void theRoom(int aDoor, int bDoor, int cDoor, int dDoor, GLuint textureA, GLuint textureB);

//many rooms pieced together for presentation
void presentationRoom(int numberOfRooms, GLuint textureA, GLuint textureB);