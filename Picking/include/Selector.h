/*
 * Selector.h
 *
 *  Created on: Dec 16, 2014
 *      Author: pim
 */

#ifndef SRC_SELECTOR_H_
#define SRC_SELECTOR_H_
#include <string>
#include <map>
#include <vector>
#include "CGFscene.h"
#include <unistd.h>
#include <math.h>
#include "CGFapplication.h"
#include "CGFappearance.h"
#include "CGFshader.h"
class Selector {
	CGFappearance* material;
	float x,y,z;
public:
	Selector();
	void moveTo(float x,float y,float z);
	void draw();
	virtual ~Selector();
};

#endif /* SRC_SELECTOR_H_ */
