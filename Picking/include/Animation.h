/*
 * Animation.h
 *
 *  Created on: 18/11/2014
 *      Author: vania
 */

#include <string>
#include "CGFscene.h"
#include "CGFapplication.h"
#include "CGFappearance.h"
#include "CGFshader.h"
#include <cmath>

#ifndef SRC_ANIMATION_H_
#define SRC_ANIMATION_H_

using namespace std;

#define PI 3.14

class Animation {

protected:
	string id;
	float startTime, span;

public:
	Animation();
	Animation(string id, float span);
	virtual void update(unsigned long t)=0;
	virtual void move()=0;
	virtual void reset()=0;
	string getId();
	virtual ~Animation();



};



#endif /* SRC_ANIMATION_H_ */
