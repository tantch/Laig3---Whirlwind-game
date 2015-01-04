/*
 * Interface.h
 *
 *  Created on: Oct 19, 2014
 *      Author: vania
 */

#include "CGFinterface.h"
#include "PickScene.h"
#include <string>
#include <vector>

#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

class Interface: public CGFinterface {
private:

public:

	virtual void processMouse(int button, int state, int x, int y);
	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer[]);
	void initGUI();
	void processGUI(GLUI_Control *control);
};

#endif /* SRC_INTERFACE_H_ */
