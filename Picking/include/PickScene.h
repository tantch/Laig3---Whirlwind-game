#ifndef PICKSCENE_H
#define PICKSCENE_H

#include "CGFscene.h"
#include "PickInterface.h"
#include "Board.h"
#include "Selector.h"
#include "Pieces.h"
class PickScene : public CGFscene
{
	friend PickInterface;
public:
	void init();
	void display();
	void pieceSelected(int id);
	void update(unsigned long millis);
	void boardSelected(int i,int j);
	~PickScene();
private:
	unsigned long lastTime;
	Pieces* pieces;
	CGFlight* light0;
	Selector* selector;
	Board* board;
	CGFobject* obj;
	CGFappearance* materialAppearance;
};

#endif
