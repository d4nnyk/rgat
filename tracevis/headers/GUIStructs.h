#pragma once
#include "stdafx.h"
//#include "GUIManagement.h"
#include "graph_display_data.h"
#include "GUIConstants.h"
#include "traceStructs.h"
#include "thread_graph_data.h"
#include "timeline.h"

struct DIFFIDS {
	int pid1 = -1;
	int pid2 = -1;
	int tid1 = -1;
	int tid2 = -1;
};

struct TITLE {
	char zoom[25] = { 0 };
	char MPos[25] = { 0 };
	char title[255] = { 0 };
	char FPS[25] = { 0 };
	char Primitives[35] = { 0 };
	char dbg[200] = { 0 };
};

struct DISPLAYMODES {
	bool wireframe = true;
	bool nodes = true;
	bool edges = true;
	bool preview = true;
	bool animation = false;
	bool heatmap = false;
	bool conditional = false;
	int diff = 0;
};

struct HEIGHTWIDTH {
	int height;
	int width;
};

struct GUI_DATA {
	vector<ALLEGRO_COLOR> lineColoursArr;
};

struct VISSTATE {
	
	ALLEGRO_DISPLAY *maindisplay = 0;
	ALLEGRO_BITMAP *mainGraphBMP = 0;
	ALLEGRO_BITMAP *previewPaneBMP = 0;
	ALLEGRO_FONT *standardFont;

	TITLE *title;
	float zoomlevel = INITIALZOOM;
	float xturn = 135;
	float yturn = -25;
	HEIGHTWIDTH size;
	bool rescale = false;
	int show_ins_text = INSTEXT_AUTO;
	int leftcolumn = 0;
	int rightcolumn = 0;

	void *widgets;
	int animationUpdate = 0;
	//animation steps over bbs. false = instructions
	bool stepBBs = true;

	bool saveInProgress = false;
	bool mouse_dragging = false;
	thread_graph_data *mouse_drag_graph = NULL;
	map <int, pair<int, int>> graphPositions;
	void *tDisplayPreview = NULL;
	float previewYAngle = -30;
	bool previewSpin = true;

	HANDLE displayMutex = CreateMutex(NULL, FALSE, NULL);

	DISPLAYMODES modes;
	thread_graph_data *activeGraph = NULL;
	void *newActiveGraph = NULL;
	int newPID = -1;
	PID_DATA *activePid = NULL;
	GUI_DATA *guidata;

	GRAPH_DISPLAY_DATA *col_pick_sphere = NULL;
	GLuint colSphereVBOs[2];
	GRAPH_DISPLAY_DATA *wireframe_sphere = NULL;
	GLuint wireframeVBOs[2];

	std::map<int, PID_DATA *> glob_piddata_map;
	HANDLE pidMapMutex = CreateMutex(NULL, false, NULL);

	timeline *timelineBuilder;

};

//screen top bottom red green
//for edge picking
struct SCREEN_EDGE_PIX {
	double leftgreen = 0;
	double rightgreen = 0;
	double topred = 0;
	double bottomred = 0;
};

