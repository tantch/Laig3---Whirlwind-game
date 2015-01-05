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
	vector<float> moveSelectedTo(int i,int j);
	void setTk(float i,float j,float k);
	void block(int id );
	void unblock(int id);
	void update(unsigned long millis);
	void draw();
	void select(int id,int pl);
	bool isSelected();
	void undoMove(int id,float x,float y,float z);
	vector<float> moveFreePieceTo(int color,int i,int j);
	virtual ~Pieces();
	bool moving();
};

#endif /* SRC_PIECES_H_ */
