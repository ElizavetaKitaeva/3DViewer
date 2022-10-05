#include "fileReader.h"

int Ftokens(FILE *objFile) {
  char *tok;
  int countTokenF = 0;
  char *crutch;
  fseek(objFile, 0, SEEK_SET);
  char *arr = NULL;
  while (!feof(objFile)) {
    size_t len;
    getline(&arr, &len, objFile);
    if (!strncmp("f ", arr, (size_t)2)) {
      tok = strtok_r(arr, "f \n", &crutch);
      while (tok != NULL) {
        tok = strtok_r(NULL, " f\n", &crutch);
        countTokenF++;
      }
    }
  }
  free(arr);
  return countTokenF;
}

void Vcounts(FILE *objFile, Model *figure) {
  fseek(objFile, 0, SEEK_SET);
  double countV = 0;
  char *arr = NULL;
  while (!feof(objFile)) {
    size_t len;
    getline(&arr, &len, objFile);
    if (!strncmp("v ", arr, (size_t)2)) {
      countV++;
    }
  }
  free(arr);
  figure->vertNumber = countV;
}

void ParsFiles(FILE *objFile, Model *figure) {
  fseek(objFile, 0, SEEK_SET);
  char *token;
  char *crutch;
  int iF = 0, iV = 0;
  figure->polNumber = Ftokens(objFile);
  figure->polygons =
      (unsigned *)calloc((figure->polNumber * 2), sizeof(unsigned));

  Vcounts(objFile, figure);
  figure->vertices = (float *)calloc((figure->vertNumber * 3), sizeof(float));

  fseek(objFile, 0, SEEK_SET);

  char *arr = NULL;
  while (!feof(objFile)) {
    size_t len;
    getline(&arr, &len, objFile);
    if (!strncmp("f ", arr, (size_t)2)) {
      token = strtok_r(arr, "f \n", &crutch);
      int first = atoi(token) - 1;
      int last = first;
      while ((token = strtok_r(NULL, " \nf", &crutch))) {
        int cur = atoi(token) - 1;
        figure->polygons[iF++] = last;
        figure->polygons[iF++] = cur;
        last = cur;
      }
      figure->polygons[iF++] = last;
      figure->polygons[iF++] = first;
    } else if (!strncmp("v ", arr, (size_t)2)) {
      token = strtok_r(arr, "v \n", &crutch);
      while (token != NULL) {
        figure->vertices[iV] = atof(token);
        token = strtok_r(NULL, "v \n", &crutch);
        iV++;
      }
    }
  }
  free(arr);
}

void destroyModel(Model *figure) {
  if (figure) {
    if (figure->polygons) free(figure->polygons);
    if (figure->vertices) free(figure->vertices);
    free(figure);
  }
}
