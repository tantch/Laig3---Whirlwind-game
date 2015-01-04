/*
 * CircularAnimation.cpp
 *
 *  Created on: 18/11/2014
 *      Author: vania
 */

#include "CircularAnimation.h"

CircularAnimation::CircularAnimation() {
	// TODO Auto-generated constructor stub

}

CircularAnimation::CircularAnimation(string id, float span,
		vector<float> center, float radius, float initAngle, float rotAngle) :
		Animation(id, span) {

	this->center = center;
	this->radius = radius;
	this->initAngle = initAngle;
	this->rotAngle = rotAngle;
	Angle = initAngle;
	lastAngle = 0;

	float radAngle = Angle * (acos(-1) / 180);
	x = radius * cos((double) radAngle);
	z = radius * cos((double) radAngle);

	calculateSpeed();
}

void CircularAnimation::update(unsigned long t) {

	if (!isFinished) {
		if (firstTime) {
			firstTime = false;
			startTime = t;
			lastTime = t;
		} else {
			float interval = (t - lastTime) / 1000.0;
			float currentSpan = (float) (t - startTime) / 1000;
			if (span < currentSpan)
				isFinished = true;
			Angle += angularSpeed * interval;
			lastTime = t;
		}
	}

}

void CircularAnimation::calculateSpeed() {
	angularSpeed = rotAngle / span;

}

void CircularAnimation::move() {
	glTranslated(center[0], center[1], center[2]);
	glRotated(Angle, 0, 1, 0);
	glTranslated(x, 0, z);

}

void CircularAnimation::reset() {
	Angle = initAngle;
	lastAngle = 0;
	float radAngle = Angle * (acos(-1) / 180);
	x = radius * cos((double) radAngle);
	z = radius * cos((double) radAngle);
	firstTime=true;
	isFinished=false;

}
CircularAnimation::~CircularAnimation() {
	// TODO Auto-generated destructor stub
}

