/*******************************************************************************************
*
*   Ground Zero Helper Functions
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <raylib.h> 

Vector2 operator + (Vector2 v1, Vector2 v2) {
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}