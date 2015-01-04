/*
 * TextApe.cpp
 *
 *  Created on: Jan 4, 2015
 *      Author: pim
 */

#include "TextApe.h"

textureSt::textureSt(string id, string file, float texlenght_s,
		float texlenght_t) {
	this->id = id;
	this->file = file;
	this->texlenght_s = texlenght_s;
	this->texlenght_t = texlenght_t;

}
map<string, textureSt*>::iterator textureMp::getTexture(string id) {
	map<string, textureSt*>::iterator ret;

	ret = textures.find(id);
	return ret;
}
void textureMp::addTexture(string id, string file, float texlenght_s,
		float texlenght_t) {
	textures.insert(
			pair<string, textureSt*>(id,
					new textureSt(id, file, texlenght_s, texlenght_t)));

}
appearanceSt::appearanceSt(string id, CGFappearance* appe,
		map<string, textureSt*>::iterator textureref, bool hasText) {
	this->id = id;
	this->appe = appe;
	this->textureref = textureref;
	this->hasText = hasText;
}
map<string, appearanceSt*>::iterator appearanceMp::getAppearance(string id) {
	map<string, appearanceSt*>::iterator ret;

	ret = appearances.find(id);
	return ret;
}
void appearanceMp::addAppearance(string id, CGFappearance* appe,
		map<string, textureSt*>::iterator textureref, bool hasText) {
	appearances.insert(
			pair<string, appearanceSt*>(id,
					new appearanceSt(id, appe, textureref, hasText)));

}
