/*
 * Plane.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: pim
 */

#include "Plane.h"

Plane::Plane(int div) {
	this->divs = div;
}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

void Plane::draw() {
	float controlPoints[4][3] =
	{ { 0.5, 0, -0.5 }, { -0.5, 0, -0.5 },
	{ 0.5, 0, 0.5 }, {- 0.5, 0, 0.5 }
	};
	float controlPointsNorm[4][3] =
	{ { 0, 1, 0 }, { 0, 1, 0 },
	{ 0, 1, 0 }, { 0, 1, 0 }
	};
	float controlPointsText[4][2] =
	{ { 0, 0 }, { 1, 0 },
	{ 0, 1 }, { 1, 1 }
	};
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 6, 2, 0, 1, 3, 2, &controlPoints[0][0]);
	glMap2f(GL_MAP2_NORMAL, 0, 1, 6, 2, 0, 1, 3, 2, &controlPointsNorm[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 4, 2, 0, 1, 2, 2, &controlPointsText[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMapGrid2f(divs, 0, 1, divs, 0, 1);
	glEvalMesh2(GL_FILL, 0, divs, 0, divs);



}

