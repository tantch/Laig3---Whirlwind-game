/*
 * Board.h
 *
 *  Created on: Dec 16, 2014
 *      Author: pim
 */

#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_
#include "Plane.h"
class Board {
	int size;
	CGFappearance* square;
	CGFappearance* tubes;
	Plane* plane;
public:
	Board(int size);
	void draw();
	virtual ~Board();
};

#endif /* SRC_BOARD_H_ */
