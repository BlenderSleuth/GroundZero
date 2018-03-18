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

#include "Building.h"

class GroundZeroRenderer;

typedef void (*closure)(GroundZeroRenderer*);

class GroundZeroRenderer {
public:
	GroundZeroRenderer();
	~GroundZeroRenderer();

	void mainloop();

	bool drawFPS = false;

    const int width = 1920;
    const int height = 1080;
private:
	void render(int deltaTime);

	void drawBuilding(Building* building);
};

#endif