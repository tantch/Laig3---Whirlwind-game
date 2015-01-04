/*
 * Lights.h
 *
 *  Created on: Jan 4, 2015
 *      Author: pim
 */

#ifndef SRC_LIGHTS_H_
#define SRC_LIGHTS_H_

#include <string>
#include <map>
#include <vector>
#include <unistd.h>
#include <math.h>
#include "CGFapplication.h"
#include "CGFappearance.h"

class lightSt {
public:
	string id;
	bool enabled;
	CGFlight* light;
	bool marker;

	lightSt(string id, CGFlight* light, bool marker, bool enabled);
};
class lightMp {
public:
	map<string, lightSt*> lights;
	lightSt* getLight(string id);
	void addLight(string id, CGFlight* light, bool marker, bool enabled);

};

#endif /* SRC_LIGHTS_H_ */
