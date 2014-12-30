/*
 * Selector.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: pim
 */

#include "Selector.h"
Selector::Selector() {
float dif[4]={1,1,0,0.6};
float spec[4]={0,0,0,0};
float amb[4]={0,0,0,0};
this->material= new CGFappearance(amb,dif,spec,120);


}
void Selector::moveTo(float x,float y,float z){
	this->x=x;
	this->y=y;
	this->z=z;
}
void Selector::draw(){
	glPushMatrix();
	material->apply();
	glTranslatef(x,y,z);
	glRotatef(-90,1,0,0);
	gluDisk(gluNewQuadric(), 0, 0.5, 30, 30);
	glPopMatrix();
}
Selector::~Selector() {
	// TODO Auto-generated destructor stub
}

