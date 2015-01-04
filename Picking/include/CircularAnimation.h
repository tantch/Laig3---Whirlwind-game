/*
 * CircularAnimation.h
 *
 *  Created on: 18/11/2014
 *      Author: vania
 */

#include "Animation.h"
#ifndef SRC_CIRCULARANIMATION_H_
#define SRC_CIRCULARANIMATION_H_

class CircularAnimation : public Animation {

private:
	vector<float> center;
	float radius,initAngle,rotAngle,Angle,x,y,z,lastAngle, angularSpeed;
	bool isFinished, firstTime;
	unsigned long startTime, lastTime;
public:
	CircularAnimation();
	CircularAnimation(string id, float span, vector<float> center, float radius, float initAngle, float rotAngle);
	void reset();
	void update(unsigned long t);
	void calculateSpeed();
	void move();
	virtual ~CircularAnimation();
};


#endif /* SRC_CIRCULARANIMATION_H_ */
