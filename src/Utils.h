/*******************************************************************************************
*
*   Ground Zero Helper Functions
*
*   This program has been created using raylib 1.8 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <iostream>
#include <raylib.h>

#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

Vector2 operator + (Vector2 v1, Vector2 v2) {
    return Vector2({v1.x + v2.x, v1.y + v2.y});
}
void operator += (Vector2& v1, Vector2 v2) {
    v1 = v1 + v2;
}

Vector2 operator - (Vector2 v1, Vector2 v2) {
    return Vector2({v1.x - v2.x, v1.y - v2.y});
}
Vector2 operator - (Vector2 v) {
    return Vector2({-v.x, -v.y});
}
void operator -= (Vector2& v1, Vector2 v2) {
    v1 = v1 - v2;
}

Vector2 operator * (Vector2 v1, float s) {
    return Vector2({v1.x * s, v1.y * s});
}
void operator *= (Vector2& v1, float s) {
    v1 = v1 * s;
}
Vector2 operator / (Vector2 v1, float s) {
    return Vector2({v1.x / s, v1.y / s});
}
void operator /= (Vector2& v1, float s) {
    v1 = v1 / s;
}

bool operator == (Vector2 v1, Vector2 v2) {
    return (v1.x == v2.x && v1.y == v2.y);
}

std::ostream& operator << (std::ostream& stream, Vector2& v) {
    stream << "(" << v.x << ", " << v.y << ")\n";
    return stream;
}

#endif // __UTILS_H_INCLUDED__
