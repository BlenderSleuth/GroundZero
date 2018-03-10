/*******************************************************************************************
*
*   Ground Zero Renderer | Display town data model
*
*   This program has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <raylib.h>
#include "Game.h"
#include "GroundZeroRenderer.h"

GroundZeroRenderer::GroundZeroRenderer() {
	InitWindow(Game::Instance()->width(), Game::Instance()->height(), "Ground Zero");
	SetTargetFPS(60);
}
GroundZeroRenderer::~GroundZeroRenderer() {  
    CloseWindow();        // Close window and OpenGL context
}

void GroundZeroRenderer::mainloop(closure runfunc) {
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        BeginDrawing();
        runfunc(this);
        EndDrawing();
    }
}

void GroundZeroRenderer::relPos(int &x, int &y) {
	x *= Game::Instance()->scale;
	y *= Game::Instance()->scale;
}