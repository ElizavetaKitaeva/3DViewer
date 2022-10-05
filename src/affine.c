#include "affine.h"

void ScaleTransform(float* vert, int size, float scaleX, float scaleY,
                    float scaleZ) {
  for (int i = 0; i < size; i += 3) {
    vert[i] *= scaleX;
    vert[i + 1] *= scaleY;
    vert[i + 2] *= scaleZ;
  }
}

void Rotate(float* vert, int size, float radX, float radY, float radZ) {
  if (radX) rotateX(vert, size, radX);
  if (radY) rotateY(vert, size, radY);
  if (radZ) rotateZ(vert, size, radZ);
}

void rotateX(float* vert, int size, float rad) {
  for (int i = 0; i < size; i += 3) {
    float tempY = vert[i + 1];
    float tempZ = vert[i + 2];
    vert[i + 1] = tempY * cos(rad) - tempZ * sin(rad);
    vert[i + 2] = tempZ * cos(rad) + tempY * sin(rad);
  }
}

void rotateY(float* vert, int size, float rad) {
  for (int i = 0; i < size; i += 3) {
    float tempX = vert[i];
    float tempZ = vert[i + 2];
    vert[i] = tempX * cos(rad) + tempZ * sin(rad);
    vert[i + 2] = tempZ * cos(rad) - tempX * sin(rad);
  }
}

void rotateZ(float* vert, int size, float rad) {
  for (int i = 0; i < size; i += 3) {
    float tempX = vert[i];
    float tempY = vert[i + 1];
    vert[i] = tempX * cos(rad) - tempY * sin(rad);
    vert[i + 1] = tempY * cos(rad) + tempX * sin(rad);
  }
}

void MoveTransform(float* vert, int size, float moveX, float moveY,
                   float moveZ) {
  for (int i = 0; i < size; i += 3) {
    vert[i] += moveX;
    vert[i + 1] += moveY;
    vert[i + 2] += moveZ;
  }
}
