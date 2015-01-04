/*
 * TextApe.h
 *
 *  Created on: Jan 4, 2015
 *      Author: pim
 */

#ifndef SRC_TEXTAPE_H_
#define SRC_TEXTAPE_H_
#include <string>
#include <map>
#include <vector>
#include <unistd.h>
#include <math.h>
#include "CGFapplication.h"
#include "CGFappearance.h"

class textureSt {
public:
	string id, file;
	float texlenght_s, texlenght_t;
	textureSt(string id, string file, float texlenght_s, float texlenght_t);
};
class textureMp {
public:
	map<string, textureSt*> textures;
	map<string, textureSt*>::iterator getTexture(string id);
	void addTexture(string id, string file, float texlenght_s,
			float texlenght_t);
};
class appearanceSt {
public:
	string id;
	bool hasText;
	map<string, textureSt*>::iterator textureref;
	CGFappearance* appe;
	appearanceSt(string id, CGFappearance* appe,
			map<string, textureSt*>::iterator textureref, bool hasText);
};

class appearanceMp {
public:
	map<string, appearanceSt*> appearances;
	map<string, appearanceSt*>::iterator getAppearance(string id);
	void addAppearance(string id, CGFappearance* appe,
			map<string, textureSt*>::iterator textureref, bool hasText);

};
#endif /* SRC_TEXTAPE_H_ */
