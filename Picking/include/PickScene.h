#ifndef PICKSCENE_H
#define PICKSCENE_H

#include "CGFscene.h"
#include "Interface.h"
#include "Board.h"
#include "Selector.h"
#include "Pieces.h"
#include "tinyxml.h"
#include "Globals.h"
#include "Cameras.h"
#include "Lights.h"
#include "TextApe.h"
#include "LinearAnimation.h"
#include "CircularAnimation.h"
class PickScene: public CGFscene {
	friend Interface;
public:
	void startAnf(char* filename);
	void readAnf();
	void activateLight(int id, bool enable);
	void undo();
	void init();
	void display();
	void parseBoard();
	void pieceSelected(int id);
	void update(unsigned long millis);
	void boardSelected(int i, int j);
	void changePlayer();
	~PickScene();

	TiXmlElement* anfElement;
	TiXmlElement* globalElements;
	TiXmlElement* cameraElements;
	TiXmlElement* lightElements;
	TiXmlElement* textureElements;
	TiXmlElement* appearanceElements;
	TiXmlElement* graphElements;
	drawingSt* draw;
	cullingSt* culling;
	lightingSt* lighting;
	cameraMp* cameras;
	lightMp* lights;
	textureMp* textures;
	appearanceMp* appearances;
	GraphMp* graph;
	vector<string> luzesId;
	vector<string> camerasId;
	AnimationMp* animationsV;
	int rotating;
	int currentPlayer=1;
	float rot;
	int activeCam = 0;
	int drawMode = 0;
	int movesMade=0;
	string msg;
	vector<vector<float> > history;
	vector<vector<int> > rcvBoard;
	unsigned long lastTime;
	Pieces* pieces;
	CGFlight* light0;
	Selector* selector;
	Board* board;
	CGFobject* obj;
	CGFappearance* materialAppearance;
};

#endif
