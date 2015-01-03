/*
 * Pieces.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: pim
 */

#include "Pieces.h"
#include  <signal.h>
Pieces::Pieces(int num,int boardSize,vector< vector<int> > board) {
	for (int i = 0; i < num; i++) {
		pieces.push_back(new Piece(false,1, boardSize +1 + ((i/25)*1), ((i/5)%5)*0.3, (i%5)+0.5+boardSize/2-2.5));
		pieces.push_back(new Piece(false,0, -1 - ((i/25)*1), ((i/5)%5)*0.3, (i%5)+0.5+boardSize/2-2.5));

	}
	for(unsigned int i=0;i< board.size();i++){
		for(unsigned int j=0;j<board[i].size();j++){
			if(board[i][j]!='0'){
				pieces.push_back(new Piece(true,board[i][j]-49, i+0.5, 0.001,j+0.5));
			}
		}
	}
	this->selectedPiece= -1;
}
void Pieces::moveSelectedTo(int i,int j){
	pieces[selectedPiece]->moveTo(i+0.5,0.001,j+0.5);
	pieces[selectedPiece]->unpick();
	pieces[selectedPiece]->placeInBoard();
	selectedPiece=-1;
}

void Pieces::draw() {
	glPushName(-1);
	glLoadName(1);
	for (unsigned int i = 0; i < pieces.size(); i++) {
		glPushName(i);
		pieces[i]->draw();
		glPopName();
	}
	glPopName();

}
void Pieces::select(int id){
	if(pieces[id]->isInBoard()){
		block(id);
		return;
	}
	if(selectedPiece != -1){
		pieces[selectedPiece]->unpick();
	}
	this->selectedPiece= id;
	pieces[selectedPiece]->pick();
	return;
}
bool Pieces::isSelected(){
	if(selectedPiece==-1){
		return false;
	}
	else{
		return true;
	}
}

Pieces::~Pieces() {
	// TODO Auto-generated destructor stub
}

void Pieces::block(int id){
	pieces[id]->block();
	blocks.push_back(id);
}
void Pieces::unblock(int id){
	pieces[id]->unblock();

}
void Pieces::update(unsigned long millis){
	for(int i=0;i<pieces.size();i++){
		pieces[i]->update(millis);
	}
}

