/*******************************************************************************************
*
*   Game | Global state data model
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include "Game.h"

Game* Game::singletonInstance = nullptr;

Game* Game::Instance() {
	if (!singletonInstance)
		singletonInstance = new Game;
	return singletonInstance;
}

int Game::width() { return this->sWidth * this->scale; }
int Game::height() { return this->sHeight * this->scale; }