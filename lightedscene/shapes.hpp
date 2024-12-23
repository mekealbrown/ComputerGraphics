//-------------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Homework #4: Lighted Scene
// Due Date --- October 23, 2024
//
// Header file containing declarations of useful functions for drawing things.
//-------------------------------------------------------------------------------
#pragma once

const float PI = 3.14159265358979323846f;
const float BACKGROUND_COLOR[] = {0.0f, 0.0f, 0.0f, 1.0f};
const float PURPLE[] = { 0.7f, 0.0f, 0.7f, 1.0f };
const float BROWN[] = {0.259, 0.118, 0.016};


struct Vertex;
struct Vector3;
void drawPyramid(const int sides, const float radius, const float height, const float color[]);
void drawPrism(int sides, float radius, float height, const float color[]);
Vector3 calculateNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);
void drawText(float x, float y, float z, const char* text);