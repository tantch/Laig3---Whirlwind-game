/*
 * Cameras.h
 *
 *  Created on: Jan 4, 2015
 *      Author: pim
 */

#ifndef SRC_CAMERAS_H_
#define SRC_CAMERAS_H_
#include <string>
#include <map>
#include <vector>
#include "CGFscene.h"
#include <unistd.h>
#include <math.h>
#include "CGFapplication.h"
using namespace std;

class cameraSt {
public:
	string id;
	virtual void print()=0;
	virtual void apply() =0;
};
class persCamSt: public cameraSt {
public:

	float near, far, angle;
	vector<float> pos, target;
	persCamSt(string id, float near, float far, float angle, vector<float> pos,
			vector<float> target);
	void print();
	void apply();
};

class orthoCamSt: public cameraSt {
public:
	string direction;
	float near, far, left, right, top, bottom;
	orthoCamSt(string id, string direction, float near, float far, float left,
			float right, float top, float bottom);
	void print();
	void apply();
};
class cameraMp {
public:
	map<string, cameraSt*>::iterator curCam;
	map<string, cameraSt*> cameras;
	map<string, cameraSt*>::iterator getCamera(char* id);
	void addOrthoCam(string id, string direction, float near, float far,
			float left, float right, float top, float bottom);
	void addPrespCam(string id, float near, float far, float angle,
			vector<float> pos, vector<float> target);

};

#endif /* SRC_CAMERAS_H_ */
