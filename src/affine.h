#ifndef AFFINE_H_
#define AFFINE_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ScaleTransform(float* vert, int size, float scaleX, float scaleY,
                    float scaleZ);
void Rotate(float* vert, int size, float radX, float radY, float radZ);
void MoveTransform(float* vert, int size, float scaleX, float scaleY,
                   float scaleZ);

void rotateX(float* vert, int size, float rad);
void rotateY(float* vert, int size, float rad);
void rotateZ(float* vert, int size, float rad);

#endif
