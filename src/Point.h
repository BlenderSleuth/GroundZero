/*******************************************************************************************
*
*   Point | (x, y) coordinates
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#ifndef __POINT_H_INCLUDED__
#define __POINT_H_INCLUDED__

struct Point {
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int x, y;
};

#endif
