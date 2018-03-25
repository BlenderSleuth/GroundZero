/*******************************************************************************************
*
*   Ground Zero Renderer | Display town data model
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __GR_RENDERER_H_INCLUDED__
#define __GR_RENDERER_H_INCLUDED__

#include "Road.h"
#include "Building.h"

class GroundZeroRenderer;

typedef void (*closure)(GroundZeroRenderer*);

class GroundZeroRenderer {
public:
	GroundZeroRenderer();
	~GroundZeroRenderer();

	void mainloop();

	bool showFPS = true;

	Color backgroundColour = (Color){0, 114, 24, 128};

    const int width = 1000;
    const int height = 1000;
private:
	void render(float deltaTime);

	void drawRoad(Road* road);
	void drawBuilding(Building* building);
};

#endif