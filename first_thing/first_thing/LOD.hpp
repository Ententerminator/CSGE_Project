#pragma once
#include "stdafx.h"

struct pos {
	float x;
	float y;
	float z;
};

void drawTree(double dist1, double dist2, double dist3);
void fractalTree(double dist);
double getDistance(double pos1x, double pos1y, double pos1z, double pos2x, double pos2y, double pos2z );
