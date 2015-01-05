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
	float dif[4] = { 1, 1, 1, 1 };
	float spec[4] = { 0.8, 0.8, 0.8, 1 };
	float amb[4] = { 0.1, 0.1, 0.1, 1 };
	this->square = new CGFappearance(dif, spec, amb, 80);
	float dif2[4] = { 0.3, 0.3, 0.3, 1 };
	float spec2[4] = { 0.3, 0.3, 0.3, 1 };
	float amb2[4] = { 0.1, 0.1, 0.1, 1 };
	this->tubes = new CGFappearance(dif2, spec2, amb2, 80);

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

	for (int i = 0; i < size; i++) {
		glPushMatrix();
		tubes->apply();
		glTranslatef(i, 0, 0);
		gluCylinder(gluNewQuadric(), 0.05, 0.05, size - 1, 10, 50);
		glPopMatrix();
		glPushMatrix();
		tubes->apply();
		glTranslatef(0, 0, i);
		glRotatef(90, 0, 1, 0);
		gluCylinder(gluNewQuadric(), 0.05, 0.05, size - 1, 10, 50);
		glPopMatrix();
	}
	glPushMatrix();
	square->apply();
	glTranslatef(-1.25, 0, -1);
	glRotatef(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, size+1.5, 30, 50);
	glPopMatrix();
	glPushMatrix();
	square->apply();
	glTranslatef(-1.25, 0, size);
	glRotatef(90, 0, 1, 0);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, size+1.5, 30, 50);
	glPopMatrix();
	glPushMatrix();
	tubes->apply();
	glTranslatef(-1, 0, -1.25);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, size+1.5, 30, 50);
	glPopMatrix();
	glPushMatrix();
	tubes->apply();
	glTranslatef(size, 0, -1.25);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, size+1.5, 30, 50);
	glPopMatrix();

	glPopMatrix();

}

Board::~Board() {
	// TODO Auto-generated destructor stub
}

