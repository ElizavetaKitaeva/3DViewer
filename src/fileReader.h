#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Model {
  unsigned *polygons;
  int polNumber;
  float *vertices;
  int vertNumber;
} Model;

int Ftokens(FILE *objFile);
void Vcounts(FILE *objFile, Model *figure);
void ParsFiles(FILE *objfile, Model *figure);
void destroyModel(Model *figure);

#endif  // FILEREADER_H_
