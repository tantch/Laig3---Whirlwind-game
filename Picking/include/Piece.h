/*
 * Piece.h
 *
 *  Created on: Dec 29, 2014
 *      Author: pim
 */

#ifndef SRC_PIECE_H_
#define SRC_PIECE_H_
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include "CGFscene.h"
#include <unistd.h>
#include <math.h>
#include "CGFapplication.h"
#include "CGFappearance.h"
#include "CGFshader.h"


class Piece {
	bool inBoard;
	bool picked;
	int moving;
	float dest[3];
	float ori[3];
	float vel[3];
	int blocked;
	float tkcl[3];
	float x,y,z;
	CGFappearance* material;
	int color;
public:
	void setTk(float i,float j,float k);
	void block();
	bool isMoving();
	void print();
	int getColor();
	float getX();
	float getY();
	float getZ();
	void update(unsigned long millis);
	void unblock();
	bool isInBoard();
	void pick();
	void unpick();
	void placeInBoard();
	void removeFromBoard();
	void draw();
	void moveTo(float x,float y,float z);
	Piece(bool inBoard,int color,float x,float y,float z);
	virtual ~Piece();
};

#endif /* SRC_PIECE_H_ */
