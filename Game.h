/*******************************************************************************************
*
*   Game | Global state data model
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__ 

class Game {
public:
    int scale = 1;
    int width();
    int height();
    int time = 0;
    static Game* Instance();

private:
    Game() {};
    const int sWidth = 800;
    const int sHeight = 450;
    static Game* singletonInstance;
};

#endif
