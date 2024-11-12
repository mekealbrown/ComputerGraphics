//-------------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Homework #6: Take that!
// Due Date --- November 13, 2024
//
// Header file containing declarations of useful functions for drawing things.
//-------------------------------------------------------------------------------
#ifndef SHAPES_H
#define SHAPES_H

const float PI = 3.14159265358979323846f;
const float BLACK[] = {0.0f, 0.0f, 0.0f, 1.0f};
const float PURPLE[] = {0.7f, 0.0f, 0.7f, 1.0f};
const float BROWN[] = {0.259, 0.118, 0.016, 1.0f};
const float GOLD[] = {1.0f, 0.84f, 0.0f, 1.0f};
const float WHITE[] = {1.0f, 1.0f, 1.0f, 1.0f};


struct Vertex;
struct Vector3;
void drawPyramid(const int sides, const float radius, const float height, const float color[]);
void drawPrism(int sides, float radius, float height, const float color[], bool textured);
Vector3 calculateNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);
void drawDrCrawleyBoard(int n, float radius, float height, const float color[]);
void drawDart(float size);
void drawText(float x, float y, float z, const char* text);

#endif