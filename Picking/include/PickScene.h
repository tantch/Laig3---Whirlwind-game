#ifndef PICKSCENE_H
#define PICKSCENE_H

#include "CGFscene.h"
#include "PickInterface.h"
#include "Board.h"
#include "Selector.h"
#include "Piece.h"
class PickScene : public CGFscene
{
	friend PickInterface;
public:
	void init();
	void display();
	void actionSelected(int i,int j);
	~PickScene();
private:
	Piece* piece;
	CGFlight* light0;
	Selector* selector;
	Board* board;
	CGFobject* obj;
	CGFappearance* materialAppearance;
};

#endif
