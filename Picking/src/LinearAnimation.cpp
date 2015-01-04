/*
 * LinearAnimation.cpp
 *
 *  Created on: 18/11/2014
 *      Author: vania
 */

#include "LinearAnimation.h"

LinearAnimation::LinearAnimation() {
	speed = 0;
	distance = 0;
	pointIt = -1;
	firstTime = true;
	isFinished = false;
	x = 0;
	y = 0;
	z = 0;
	dx = 0;
	dy = 0;
	dz = 0;

}

LinearAnimation::LinearAnimation(string id, float span,
		vector<vector<float> > ControlPoints) :
		Animation(id, span) {

	dx = 0;
	dy = 0;
	dz = 0;
	speed = 0;
	distance = 0;
	pointIt = -1;
	firstTime = true;
	isFinished = false;
	this->ControlPoints = ControlPoints;
	calculateSpeed();
	nextPoint();
}

void LinearAnimation::addPoint(float x, float y, float z) {
	vector<float> v;
	v.push_back(x);
	v.push_back(y);
	v.push_back(z);
	ControlPoints.push_back(v);
}

void LinearAnimation::update(unsigned long t) {

	if (!isFinished) {
		if (firstTime) {
			lastTime = t;
			firstTime = false;
			startTime = t;

		} else {
			float interval = (t - lastTime) / 1000.0;
			float currentSpan = (float) (t - startTime) / 1000.0;
			if (span < currentSpan)
				isFinished = true;
			x += dx * speed * interval;
			y += dy * speed * interval;
			z += dz * speed * interval;

			if (validatePassage())
				nextPoint();

			lastTime = t;

		}
	}
}

bool LinearAnimation::validatePassage() {
	int nextPoint = pointIt + 1;
	if (nextPoint == ControlPoints.size())
		nextPoint = 0;
	if (dx > 0) {
		if (x > ControlPoints[nextPoint][0])
			return true;
	} else if (dx < 0) {
		if (x < ControlPoints[nextPoint][0])
			return true;
	}
	if (dy > 0) {
		if (y > ControlPoints[nextPoint][1])
			return true;
	} else if (dy < 0) {
		if (y < ControlPoints[nextPoint][1])
			return true;
	}
	if (dz > 0) {
		if (z > ControlPoints[nextPoint][2])
			return true;
	} else if (dz < 0) {
		if (z < ControlPoints[nextPoint][2])
			return true;
	}
	return false;

}

void LinearAnimation::nextPoint() {

	pointIt++;
	if (pointIt == ControlPoints.size() - 2)
		isFinished = true;

	dx = ControlPoints[pointIt + 1][0] - ControlPoints[pointIt][0];
	dy = ControlPoints[pointIt + 1][1] - ControlPoints[pointIt][1];
	dz = ControlPoints[pointIt + 1][2] - ControlPoints[pointIt][2];

	float currentDistance = sqrt(dx * dx + dy * dy + dz * dz);
	dx /= currentDistance;
	dy /= currentDistance;
	dz /= currentDistance;

	x = ControlPoints[pointIt][0];
	y = ControlPoints[pointIt][1];
	z = ControlPoints[pointIt][2];

}

void LinearAnimation::move() {
	glTranslated(x, y, z);
}
void LinearAnimation::reset() {
	dx = 0;
	dy = 0;
	dz = 0;
	pointIt = -1;
	x = ControlPoints[0][0];
	y = ControlPoints[0][1];
	z = ControlPoints[0][2];

	isFinished=false;
	firstTime=true;
	nextPoint();

}

void LinearAnimation::calculateSpeed() {
	distance = 0.0;
	vector<float> p1;
	vector<float> p2;
	for (int i = 0; i < ControlPoints.size() - 1; i++) {
		p1 = ControlPoints[i];
		p2 = ControlPoints[i + 1];

		float x = p1[0] - p2[0];
		float y = p1[1] - p2[1];
		float z = p1[2] - p2[2];

		distance += sqrt(x * x + y * y + z * z);
	}

	speed = distance / span;

	x = ControlPoints[0][0];
	y = ControlPoints[0][1];
	z = ControlPoints[0][2];

}

LinearAnimation::~LinearAnimation() {
	// TODO Auto-generated destructor stub
}

