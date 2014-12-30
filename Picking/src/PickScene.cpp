#include "PickScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include "ExampleObject.h"

#include <math.h>

#include "CGFappearance.h"

#define NUM_OBJS 7
#define NUM_ROWS 5
#define NUM_COLS 4

void PickScene::init() {
	// normal init, no changes needed

	// Enables lighting computations
	glEnable(GL_TEXTURE_2D);

	// Sets up some lighting parameters

	// Declares and enables a light
	float light0_pos[4] = { 4.0, 6.0, 5.0, 1.0 };
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->enable();

	glEnable(GL_LIGHTING);

	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient); // Define ambient light

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	// Defines a default normal
	glNormal3f(0, 0, 1);

	obj = new ExampleObject();
	board = new Board(10);
	piece = new Piece(2,5.5,0.001,5.5);
	selector = new Selector();
	materialAppearance = new CGFappearance();
}

void PickScene::display() {

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	// Draw (and update) light
	light0->draw();

	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN feature demos

	materialAppearance->apply();

	// draw opaques
	board->draw();

	piece->draw();
	//draw transperancys
	selector->draw();

	// ---- END feature demos

	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}
void PickScene::actionSelected(int i,int j){
	selector->moveTo(i+0.5,0.001,j+0.5);

}

PickScene::~PickScene() {
	delete (materialAppearance);
	delete (obj);
	delete (light0);
}
