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
#include <vector>
#include "CGFscene.h"
#include <unistd.h>
#include <math.h>
#include "CGFapplication.h"
#include "CGFappearance.h"
#include "CGFshader.h"

class Piece {
	float x,y,z;
	CGFappearance* material;
	int color;
public:
	void draw();
	void moveTo(float x,float y,float z);
	Piece(int color,float x,float y,float z);
	virtual ~Piece();
};

#endif /* SRC_PIECE_H_ */
