/*
 * Board.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: pim
 */

#include "Board.h"

Board::Board(int size) {

	this->size = size;
	this->plane = new Plane(10);
	float dif[4] = { 1, 1, 1,1};
	float spec[4] = { 0.8, 0.8, 0.8,1};
	float amb[4] = { 0.1, 0.1, 0.1,1};
	this->square = new CGFappearance(dif,spec,amb,80);
	this->square->setTexture("square.png");

}
void Board::draw() {

	glPushMatrix();
	square->apply();
	glTranslatef(0.5, 0, 0.5);
	glPushName(-1);
	glLoadName(0);
	for (int r = 0; r < size; r++) {
		glPushMatrix();
		glTranslatef(0, 0, r);
		glPushName(r);
		for (int c = 0; c < size; c++) {
			glPushMatrix();
			glTranslatef(c, 0, 0);
			glRotatef(90, 0, 1, 0);
			glPushName(c);
			this->plane->draw();
			glPopName();
			glPopMatrix();
		}
		glPopName();
		glPopMatrix();
	}
	glPopName();
	glPopMatrix();

}

Board::~Board() {
	// TODO Auto-generated destructor stub
}

