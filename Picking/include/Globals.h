/*
 * Globals.h
 *
 *  Created on: Jan 4, 2015
 *      Author: pim
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_
#include <string>
#include <map>
#include <vector>
#include <unistd.h>
#include <math.h>
using namespace std;
class drawingSt {
public:
	string mode;
	string shading;
	vector<float> background;
};
class cullingSt {
public:
	string face;
	string order;
};
class lightingSt {
public:
	bool doublesided;
	bool local;
	bool enabled;
	vector<float> ambient;
};



#endif /* SRC_GLOBALS_H_ */
