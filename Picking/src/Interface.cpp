/*
 * Interface.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: vania
 */

#include "Interface.h"

using namespace std;

void Interface::initGUI() {
	GLUI_Panel *general = addPanel("Opcoes", 1);
	addColumnToPanel(general);
	GLUI_Panel *luzesPanel = addPanelToPanel(general, "Luzes", 1);

	map<string, lightSt*>::iterator it =
			((PickScene*) scene)->lights->lights.begin();
	int i = 0;
	for (it = ((PickScene*) scene)->lights->lights.begin();
			it != ((PickScene*) scene)->lights->lights.end(); it++) {

		string str = it->first;
		char * writable = new char[str.size() + 1];
		copy(str.begin(), str.end(), writable);
		writable[str.size()] = '\0';

		if (it->second->enabled == true) {
			addCheckboxToPanel(luzesPanel, writable, NULL, i)->set_int_val(1);
		} else {
			addCheckboxToPanel(luzesPanel, writable, NULL, i)->set_int_val(0);
		}
		delete[] writable;
		((PickScene*) scene)->luzesId.push_back(it->second->id);
		i++;
	}

	addColumnToPanel(general);
	GLUI_Panel *camerasPanel = addPanelToPanel(general, "Camaras", 1);
	GLUI_RadioGroup *cameraList = addRadioGroupToPanel(camerasPanel,
			&((PickScene*) scene)->activeCam);

	std::map<std::string, cameraSt*>::iterator itc =
			((PickScene*) scene)->cameras->cameras.begin();
	i = 0;
	for (itc = ((PickScene*) scene)->cameras->cameras.begin();
			itc != ((PickScene*) scene)->cameras->cameras.end(); itc++) {

		string str = itc->first;
		char * writable = new char[str.size() + 1];
		copy(str.begin(), str.end(), writable);
		writable[str.size()] = '\0';

		if (itc == ((PickScene*) scene)->cameras->curCam)
			addRadioButtonToGroup(cameraList, writable)->set_int_val(1);
		else
			addRadioButtonToGroup(cameraList, writable)->set_int_val(0);

		delete[] writable;
		((PickScene*) scene)->camerasId.push_back(itc->second->id);
		i++;
	}

	addRadioButtonToGroup(cameraList, "Default")->set_int_val(0);

	addColumnToPanel(general);
	GLUI_Panel *drawPanel = addPanelToPanel(general, "Draw Mode", 1);
	GLUI_RadioGroup *drawList = addRadioGroupToPanel(drawPanel,
			&((PickScene*) scene)->drawMode);
	addRadioButtonToGroup(drawList, "Fill");
	addRadioButtonToGroup(drawList, "Line");
	addRadioButtonToGroup(drawList, "Point");
	addColumnToPanel(general);

	GLUI_Panel *undoPanel = addPanelToPanel(general, "Undo", 1);
	GLUI_Button *undo = addButtonToPanel(undoPanel, "Undo", 13);
	GLUI_Button *changePlayer = addButtonToPanel(undoPanel, "Finish Turn", 14);

}

void Interface::processGUI(GLUI_Control *ctrl) {

	cout << "user id =" << ctrl->user_id << endl;
	if (ctrl->user_id >= 0) {
		if (ctrl->user_id == 13) {
			((PickScene*) scene)->undo();
		} else if(ctrl->user_id==14){
			((PickScene*) scene)->changePlayer();
		}else if (ctrl->get_int_val() == 1) {
			((PickScene*) scene)->activateLight(ctrl->user_id, true);
		} else {
			((PickScene*) scene)->activateLight(ctrl->user_id, false);
		}
	}
}
// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

void Interface::processMouse(int button, int state, int x, int y) {
	CGFinterface::processMouse(button, state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x, y);
}

void Interface::performPicking(int x, int y) {
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer(BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0,
			5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void Interface::processHits(GLint hits, GLuint buffer[]) {
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected = NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i = 0; i < hits; i++) {
		int num = *ptr;
		ptr++;
		GLuint z1 = *ptr;
		ptr++;
		ptr++;
		if (z1 < mindepth && num > 0) {
			mindepth = z1;
			selected = ptr;
			nselected = num;
		}
		for (int j = 0; j < num; j++)
			ptr++;
	}

	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected != NULL) {

		// this should be replaced by code handling the picked object's ID's (stored in "selected"),
		// possibly invoking a method on the scene class and passing "selected" and "nselected"

		if (selected[0] == 0) { //place on board selected
			printf("Picked ID's: ");
			for (int i = 0; i < nselected; i++)
				printf("%d ", selected[i]);
			printf("\n");
			((PickScene*) scene)->boardSelected(selected[2], selected[1]);
		} else if (selected[0] == 1) { //pick piece
			printf("piece %d selected \n", selected[1]);
			((PickScene*) scene)->pieceSelected(selected[1]);
		}
	} else
		printf("Nothing selected while picking \n");
}
