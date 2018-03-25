/*******************************************************************************************
*
*   Ground Zero Renderer | Display town data model
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __RENDERER_H_INCLUDED__
#define __RENDERER_H_INCLUDED__

#include "Building.h"
#include "Road.h"

class Renderer {
public:
	Renderer();
	~Renderer();

	void mainloop();

	bool showFPS = true;

	Color backgroundColour = BLACK;

    const int width = 1000;
    const int height = 1000;

private:
	void render(float deltaTime);

	void drawRoad(Road* road);
	void drawBuilding(Building* building);
};

#endif // __RENDERER_H_INCLUDED__