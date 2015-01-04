/*
 * Cameras.cpp
 *
 *  Created on: Jan 4, 2015
 *      Author: pim
 */

#include "Cameras.h"
persCamSt::persCamSt(string id, float near, float far, float angle,
		vector<float> pos, vector<float> target) {
	this->id = id;
	this->near = near;
	this->angle = angle;
	this->near = near;
	this->far = far;
	this->pos = pos;
	this->target = target;

}
void persCamSt::print() {
	printf(" near : %f \n far: %f", near, far);
}
void persCamSt::apply() {
	float ratio = ((float) CGFapplication::width)
			/ ((float) CGFapplication::height);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(angle, ratio, near, far);
	glPopMatrix();
	gluLookAt(pos[0], pos[1], pos[2], target[0], target[1], target[2], 0, 1, 0);
}

orthoCamSt::orthoCamSt(string id, string direction, float near, float far,
		float left, float right, float top, float bottom) {
	this->id = id;
	this->direction = direction;
	this->near = near;
	this->far = far;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
	printf(" near = %f \n far: %f\n", near, far);
}
void orthoCamSt::print() {
	printf(" id%s near = %f \n far: %f\n", id.c_str(), near, far);
}
void orthoCamSt::apply() {
	float ratio = ((float) CGFapplication::width)
			/ ((float) CGFapplication::height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(this->left * ratio, this->right * ratio, this->bottom, this->top,
			this->near, this->far);
	if (direction == "x")
		glRotatef(-90, 0, 1, 0);
	if (direction == "y")
		glRotatef(90, 1, 0, 0);
}

map<string, cameraSt*>::iterator cameraMp::getCamera(char* id) {
	map<string, cameraSt*>::iterator ret;
	ret = cameras.find(id);
	return ret;
}
void cameraMp::addOrthoCam(string id, string direction, float near, float far,
		float left, float right, float top, float bottom) {
	cameras.insert(
			pair<string, cameraSt*>(id,
					new orthoCamSt(id, direction, near, far, left, right, top,
							bottom)));

}
void cameraMp::addPrespCam(string id, float near, float far, float angle,
		vector<float> pos, vector<float> target) {

	cameras.insert(
			pair<string, cameraSt*>(id,
					new persCamSt(id, near, far, angle, pos, target)));

}
