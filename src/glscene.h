#ifndef GLSCENE_H
#define GLSCENE_H
#ifdef __APPLE__
// Defined before OpenGL and GLUT includes to avoid deprecation messages
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif
#include <mainwindow.h>

#include <QtOpenGLWidgets/QOpenGLWidget>

#include "fileReader.h"

typedef struct floatColors {
  float red;
  float green;
  float blue;
} floatColors;

class glScene : public QOpenGLWidget {
  Q_OBJECT
 public:
  glScene(QWidget *parent);
  void getModelData(Model *model);

 public slots:
  void getSettings(saveSettings *settings);
  void updateSettings();
  void affineUpdate();

 private:
  float xRot, yRot, zRot;
  QPoint mPos;
  Model *Data = NULL;
  saveSettings *settings = NULL;
  int currentPerspective = -1, currentDotType = -1;
  double zoomScale = 1;
  bool settingsUpdated = true;
  floatColors backColor, vertColor, polColor;
  void drawFigure(float *arr, unsigned *pol);
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};

#endif  // GLSCENE_H
