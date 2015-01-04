/*
 * Lights.cpp
 *
 *  Created on: Jan 4, 2015
 *      Author: pim
 */

#include "Lights.h"

lightSt::lightSt(string id, CGFlight* light, bool marker, bool enabled) {
	this->id = id;
	this->light = light;
	this->marker = marker;
	this->enabled = enabled;
}
lightSt* lightMp::getLight(string id) {
	lightSt* ret;

	ret = lights.find(id)->second;
	return ret;
}
void lightMp::addLight(string id, CGFlight* light, bool marker, bool enabled) {
	lights.insert(
			pair<string, lightSt*>(id,
					new lightSt(id, light, marker, enabled)));

}
