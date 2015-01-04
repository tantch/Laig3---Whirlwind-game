/*
 * LinearAnimation.h
 *
 *  Created on: 18/11/2014
 *      Author: vania
 */

#include "Animation.h"

#include <vector>

#ifndef SRC_LINEARANIMATION_H_
#define SRC_LINEARANIMATION_H_

using namespace std;

class LinearAnimation : public Animation{


private:
	vector< vector<float> > ControlPoints;
	float speed, distance;
	bool firstTime, isFinished;
	int pointIt;
	long lastTime;
	float dx,dy,dz;//current distance
	float x,y,z;//current position

public:
	LinearAnimation();
	LinearAnimation(string id, float span,vector< vector<float> > ControlPoints);
	void addPoint(float x,float y, float z);
	void update(unsigned long t);
	bool validatePassage();
	void nextPoint();
	void move();
	void reset();
	void calculateSpeed();
	virtual ~LinearAnimation();



};

#endif /* SRC_LINEARANIMATION_H_ */
