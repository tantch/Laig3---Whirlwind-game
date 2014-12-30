
#ifndef SRC_PLANE_H_
#define SRC_PLANE_H_
#include <string>
#include <map>
#include <vector>
#include "CGFscene.h"
#include <unistd.h>
#include <math.h>
#include "CGFapplication.h"
#include "CGFappearance.h"
#include "CGFshader.h"
class Plane{
public:
	Plane(int div);
	virtual ~Plane();
	void draw();

	int divs;
};

#endif /* SRC_PLANE_H_ */
