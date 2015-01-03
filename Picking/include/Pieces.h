/*
 * Pieces.h
 *
 *  Created on: Dec 30, 2014
 *      Author: pim
 */

#ifndef SRC_PIECES_H_
#define SRC_PIECES_H_
#include "Piece.h"

class Pieces {
	vector <int> blocks;
	vector <Piece*> pieces;
	int selectedPiece;

public:
	Pieces(int num,int boardSize,vector< vector<int> > board);
	void moveSelectedTo(int i,int j);
	void block(int id );
	void unblock(int id);
	void update(unsigned long millis);
	void draw();
	void select(int id);
	bool isSelected();
	virtual ~Pieces();
};

#endif /* SRC_PIECES_H_ */
