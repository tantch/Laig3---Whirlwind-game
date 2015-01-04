#ifndef DATAS.H
#define DATAS.H
#include "Animation.h"
#include <string>
#include <map>
#include <vector>
#include "CGFscene.h"
#include <unistd.h>
#include <math.h>
#include "TextApe.h"
#include "CGFapplication.h"
#include "CGFappearance.h"
#include "CGFshader.h"
using namespace std;
#define PI  3.14159265359

class PrimSt {
public:
	virtual void draw()=0;
	virtual void draw(textureSt* t)=0;
};

class RectangleSt: public PrimSt {
public:
	vector<float> xy1, xy2;
	RectangleSt(vector<float> xy1, vector<float> xy2) {
		this->xy1 = xy1;
		this->xy2 = xy2;
	}
	void draw(textureSt *t) {
		//printf("hereisnide\n");
		//printf("texte : %s\n", t->id.c_str());
		float lenT = t->texlenght_s, heiT = t->texlenght_t, lenO = xy2[0]
				- xy1[0], heiO = xy2[1] - xy1[1];
		float xT, yT;
		//printf("hereisnide\n");
		xT = lenO / lenT;
		yT = heiO / heiT;
		glBegin(GL_POLYGON);
		glNormal3f(xy1[0], xy1[1], 1);
		glTexCoord2f(0, 0);
		glVertex2f(xy1[0], xy1[1]);
		glNormal3f(xy2[0], xy1[1], 1);
		glTexCoord2f(xT, 0);
		glVertex2f(xy2[0], xy1[1]);
		glNormal3f(xy2[0], xy2[1], 1);
		glTexCoord2f(xT, yT);
		glVertex2f(xy2[0], xy2[1]);
		glNormal3f(xy1[0], xy2[1], 1);
		glTexCoord2f(0, yT);
		glVertex2f(xy1[0], xy2[1]);
		glEnd();
		//printf("hereisnide\n");
	}
	void draw() {
		glBegin(GL_POLYGON);
		glNormal3f(xy1[0], xy1[1], 1);
		glTexCoord2f(0, 0);
		glVertex2f(xy1[0], xy1[1]);
		glNormal3f(xy2[0], xy1[1], 1);
		glTexCoord2f(1, 0);
		glVertex2f(xy2[0], xy1[1]);
		glNormal3f(xy2[0], xy2[1], 1);
		glTexCoord2f(1, 1);
		glVertex2f(xy2[0], xy2[1]);
		glNormal3f(xy1[0], xy2[1], 1);
		glTexCoord2f(0, 1);
		glVertex2f(xy1[0], xy2[1]);
		glEnd();
	}
};

class TriangleSt: public PrimSt {
public:
	vector<float> xyz1, xyz2, xyz3;
	float normal[3];
	TriangleSt(vector<float> xyz1, vector<float> xyz2, vector<float> xyz3) {
		this->xyz1 = xyz1;
		this->xyz2 = xyz2;
		this->xyz3 = xyz3;
		float v[3], u[3];
		v[0] = xyz2[0] - xyz1[0];
		v[1] = xyz2[1] - xyz1[1];
		v[2] = xyz2[2] - xyz1[2];
		u[0] = xyz3[0] - xyz1[0];
		u[1] = xyz3[1] - xyz1[1];
		u[2] = xyz3[2] - xyz1[2];
		normal[0] = u[1] * v[2] - u[2] * v[1];
		normal[1] = u[2] * v[0] - u[0] * v[2];
		normal[2] = u[0] * v[1] - u[1] * v[0];
	}
	void draw() {
		glBegin(GL_TRIANGLES);
		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2f(0, 0);
		glVertex3f(xyz1[0], xyz1[1], xyz1[2]);
		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2f(1, 0);
		glVertex3f(xyz2[0], xyz2[1], xyz2[2]);
		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2f(0.5, 1);
		glVertex3f(xyz3[0], xyz3[1], xyz3[2]);
		glEnd();

	}
	void draw(textureSt *t) {
		float lenT = t->texlenght_s, heiT = t->texlenght_t, lenO = xyz1[0]
				- xyz2[0], heiO = xyz3[1] - xyz1[1];
		float xT, yT;

		xT = lenO / lenT;
		yT = heiO / heiT;

		glBegin(GL_TRIANGLES);

		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2f(0, 0);
		glVertex3f(xyz1[0], xyz1[1], xyz1[2]);

		glNormal3f(normal[0], xyz2[1], normal[2]);
		glTexCoord2f(xT, 0);
		glVertex3f(xyz2[0], xyz2[1], xyz2[2]);

		glNormal3f(normal[0], normal[1], normal[2]);
		glTexCoord2f(xT * 0.5, yT);
		glVertex3f(xyz3[0], xyz3[1], xyz3[2]);
		glEnd();

	}

};
class CylinderSt: public PrimSt {
public:
	float base, top, height;
	int slices, stacks;
	CylinderSt(float base, float top, float height, int slices, int stacks) {
		this->base = base;
		this->top = top;
		this->height = height;
		this->slices = slices;
		this->stacks = stacks;
	}
	void draw() {

		GLUquadric * quad, *botD, *topD;
		botD = gluNewQuadric();
		topD = gluNewQuadric();
		gluQuadricNormals(botD, GL_SMOOTH);
		gluQuadricNormals(topD, GL_SMOOTH);
		gluQuadricTexture(botD, GL_TRUE);
		gluQuadricTexture(topD, GL_TRUE);

		glPushMatrix();
		glTranslated(0, 0, height);
		gluDisk(topD, 0, top, slices, stacks);
		glPopMatrix();

		glPushMatrix();
		glRotated(180, 0, 1, 0);
		gluDisk(botD, 0, base, slices, stacks);
		glPopMatrix();

		quad = gluNewQuadric();
		gluQuadricNormals(quad, GL_SMOOTH);
		gluQuadricTexture(quad, GL_TRUE);
		gluCylinder(quad, base, top, height, slices, stacks);

		gluDeleteQuadric(quad);
		gluDeleteQuadric(botD);
		gluDeleteQuadric(topD);
	}
	void draw(textureSt* t) {

		GLUquadric * quad, *botD, *topD;
		botD = gluNewQuadric();
		topD = gluNewQuadric();
		gluQuadricNormals(botD, GL_SMOOTH);
		gluQuadricNormals(topD, GL_SMOOTH);
		gluQuadricTexture(botD, GL_TRUE);
		gluQuadricTexture(topD, GL_TRUE);

		glPushMatrix();
		glTranslated(0, 0, height);
		gluDisk(topD, 0, top, slices, stacks);
		glPopMatrix();

		glPushMatrix();
		glRotated(180, 0, 1, 0);
		gluDisk(botD, 0, base, slices, stacks);
		glPopMatrix();

		quad = gluNewQuadric();
		gluQuadricNormals(quad, GL_SMOOTH);
		gluQuadricTexture(quad, GL_TRUE);
		gluCylinder(quad, base, top, height, slices, stacks);

		gluDeleteQuadric(quad);
		gluDeleteQuadric(botD);
		gluDeleteQuadric(topD);
	}
};

class SphereSt: public PrimSt {
public:
	float radius;
	int slices, stacks;
	SphereSt(float radius, int slices, int stacks) {
		this->radius = radius;
		this->slices = slices;
		this->stacks = stacks;
	}
	void draw() {
		GLUquadric *sphere = gluNewQuadric();
		gluQuadricTexture(sphere, GL_TRUE);
		gluQuadricNormals(sphere, GL_SMOOTH);
		gluSphere(sphere, radius, slices, stacks);
		gluDeleteQuadric(sphere);
	}
	void draw(textureSt* t) {
		GLUquadric *sphere = gluNewQuadric();
		gluQuadricTexture(sphere, GL_TRUE);
		gluQuadricNormals(sphere, GL_SMOOTH);
		gluSphere(sphere, radius, slices, stacks);
		gluDeleteQuadric(sphere);
	}
};

class TorusSt: public PrimSt {
public:
	float inner, outer;
	int slices, loops;
	TorusSt(float inner, float outer, int slices, int loops) {
		this->inner = inner;
		this->outer = outer;
		this->slices = slices;
		this->loops = loops;
	}
	void draw() {
		glutSolidTorus(inner, outer, slices, loops);
	}
	void draw(textureSt *t) {
		double pi = acos(-1.0);
		float vNormal[3];
		double majorStep = 2.0f * pi / slices;
		double minorStep = 2.0f * pi / loops;
		int i, j;
		for (i = 0; i < slices; ++i) {
			double a0 = i * majorStep;
			double a1 = a0 + majorStep;
			GLfloat x0 = (GLfloat) cos(a0);
			GLfloat y0 = (GLfloat) sin(a0);
			GLfloat x1 = (GLfloat) cos(a1);
			GLfloat y1 = (GLfloat) sin(a1);
			glBegin(GL_TRIANGLE_STRIP);
			for (j = 0; j <= loops; ++j) {
				double b = j * minorStep;
				GLfloat c = (GLfloat) cos(b);
				GLfloat r = inner * c + outer;
				GLfloat z = inner * (GLfloat) sin(b);
				// First point
				glTexCoord2f((float) (i) / (float) (loops),
						(float) (j) / (float) (slices));
				vNormal[0] = x0 * c;
				vNormal[1] = y0 * c;
				vNormal[2] = z / inner;
				//gltNormalizeVector(vNormal);
				glNormal3fv(vNormal);
				glVertex3f(x0 * r, y0 * r, z);
				glTexCoord2f((float) (i + 1) / (float) (loops),
						(float) (j) / (float) (slices));
				vNormal[0] = x1 * c;
				vNormal[1] = y1 * c;
				vNormal[2] = z / inner;
				glNormal3f(vNormal[0], vNormal[1], vNormal[2]);
				glVertex3f(x1 * r, y1 * r, z);
			}
			glEnd();
		}

	}
};
class AnimationMp {
public:
	map<string, Animation*> animations;
	map<string, Animation*>::iterator getAnimation(string id) {
		map<string, Animation*>::iterator ret;

		ret = animations.find(id);
		return ret;
	}
	void addAnimation(string id, Animation* anim) {
		animations.insert(pair<string, Animation*>(id, anim));

	}

};
class NodeSt {
public:
	string id;
	bool usingDL;
	unsigned int dl;
	float matrix[16];
	vector<map<string, Animation*>::iterator> animationsIds;
	map<string, appearanceSt*>::iterator appearanceId;
	vector<map<string, NodeSt>::iterator> descendents;
	vector<PrimSt*> primitives;

	NodeSt(string id, map<string, appearanceSt*>::iterator appearanceId,
			vector<map<string, NodeSt>::iterator> descendents,
			vector<PrimSt*> primitives, bool usingDL) {
		this->id = id;
		this->appearanceId = appearanceId;
		this->descendents = descendents;
		this->primitives = primitives;
		this->usingDL = usingDL;
		dl = 0;

	}
	NodeSt() {

	}

};
class GraphMp {
public:
	int dlcount = 0;
	map<string, NodeSt>::iterator rootId;
	map<string, NodeSt> nodes;
	map<string, NodeSt>::iterator getNode(string id) {
		map<string, NodeSt>::iterator ret;
		if ((ret = nodes.find(id)) == nodes.end()) {
			nodes.insert(pair<string, NodeSt>(id, NodeSt()));
			ret = nodes.find(id);

		}
		return ret;
	}
	void addNode(string id, map<string, appearanceSt*>::iterator appearanceId,
			vector<map<string, NodeSt>::iterator> descendents,
			vector<PrimSt*> primitives, bool usingDL) {
		if ((nodes.find(id)) == nodes.end()) {

			nodes.insert(
					pair<string, NodeSt>(id,
							NodeSt(id, appearanceId, descendents, primitives,
									usingDL)));
		} else {
			nodes.find(id)->second = NodeSt(id, appearanceId, descendents,
					primitives, usingDL);
		}
	}
	void draw(map<string, appearanceSt*>::iterator appearanceId) {
		draw(rootId, appearanceId);
	}
	void draw(map<string, NodeSt>::iterator node,
			map<string, appearanceSt*>::iterator appearanceId) {
		NodeSt nod = node->second;
		//printf("visiting node %s \n", nod.id.c_str());
		bool useText = true;
		map<string, appearanceSt*>::iterator next = appearanceId;
		if (nod.usingDL) {
			glCallList(nod.dl);

		} else {
			glPushMatrix();
			for(int i=0;i<nod.animationsIds.size();i++){
				nod.animationsIds[i]->second->move();
			}
			glMultMatrixf(nod.matrix);
			if (nod.appearanceId->second->id != "inherit") {

				nod.appearanceId->second->appe->apply();
				if (nod.appearanceId->second->hasText) {
					//printf("here\n");
					next = nod.appearanceId;
					useText = true;
				} else {
					useText = false;
				}
			} else {

				appearanceId->second->appe->apply();
				if (appearanceId->second->hasText) {
					useText = true;
				} else {
					useText = false;
				}
			}
			for (int i = 0; i < nod.primitives.size(); i++) {
				if (useText) {

					nod.primitives[i]->draw(next->second->textureref->second);
				} else
					nod.primitives[i]->draw();
			}
			for (int i = 0; i < nod.descendents.size(); i++) {
				draw(nod.descendents[i], next);
			}
			glPopMatrix();
		}
	}

};
#endif
