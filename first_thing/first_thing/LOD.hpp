#pragma once
#include "stdafx.h"

struct pos {
	float x;
	float y;
	float z;
};

void drawTree();
double getDistance(double pos1x, double pos1y, double pos1z, double pos2x, double pos2y, double pos2z );
