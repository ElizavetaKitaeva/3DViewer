#include "glscene.h"

glScene::glScene(QWidget* parent) : QOpenGLWidget(parent) {}

void glScene::resizeGL(int w, int h) {  // Channging size of window
  glViewport(0, 0, w, h);
  QPainterPath path;
  path.addRoundedRect(this->rect(), 15, 15);
  QRegion mask = QRegion(path.toFillPolygon().toPolygon());
  this->setMask(mask);
}

void glScene::paintGL() {
  glClearColor(backColor.red, backColor.green, backColor.blue, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (currentPerspective != settings->projection) {
    double maxX = 5, minX = -5, maxY = 5, minY = -5;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (!settings->projection) {
      glOrtho(minX, maxX, minY, maxY, -100000, 10000);
      currentPerspective = CENTRAL;
    } else {
      glFrustum(-0.1, 0.1, -0.1, 0.1, 0.5, 100);
      currentPerspective = PARALLEL;
    }
    glMatrixMode(GL_MODELVIEW);
  }
  if (currentDotType != settings->vertType) {
    if (settings->vertType) {
      if (settings->vertType == CIRCLE) {
        glEnable(GL_POINT_SMOOTH);  // Circle dots
        currentDotType = 1;
      } else {
        glDisable(GL_POINT_SMOOTH);
        currentDotType = 2;
      }
    } else {
      currentDotType = 0;
    }
  }
  glLineWidth(settings->edgesThickness);
  if (settings->edgesMethod) {
    glLineStipple(1, 0xFF);  // Dashed lines
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glTranslatef(0, 0, -2);
  glScaled(zoomScale, zoomScale, zoomScale);
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  if (settingsUpdated) {
    settingsUpdated = false;
    updateSettings();
  }
  if (Data) {
    unsigned* pol = this->Data->polygons;
    float* figure = this->Data->vertices;
    drawFigure(figure, pol);
  }
}

void glScene::initializeGL() { glEnable(GL_DEPTH_TEST); }

void glScene::drawFigure(float* ver, unsigned* pol) {
  glEnableClientState(GL_VERTEX_ARRAY);  // Allowing OpenGl to use buffer
  glVertexPointer(3, GL_FLOAT, 0, ver);
  glColor3f(polColor.red, polColor.green, polColor.blue);
  glDrawElements(GL_LINES, this->Data->polNumber * 2, GL_UNSIGNED_INT, pol);
  if (settings->vertType) {
    glColor3f(vertColor.red, vertColor.green, vertColor.blue);
    glPointSize(settings->sizeVert);
    glDrawElements(GL_POINTS, this->Data->polNumber * 2, GL_UNSIGNED_INT, pol);
  }
  glClearColor(backColor.red, backColor.green, backColor.blue, 0);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glScene::wheelEvent(QWheelEvent* mo) {
  QPoint numDegrees = mo->angleDelta();
  if (numDegrees.y() < 0) {
    zoomScale = zoomScale / 1.1;
  }
  if (numDegrees.y() > 0) {
    zoomScale = zoomScale * 1.1;
  }

  update();
}

void glScene::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void glScene::mouseMoveEvent(QMouseEvent* mo) {
  xRot += 0.5 / M_PI * (mo->pos().y() - mPos.y());  //  Rotation
  yRot += 0.5 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void glScene::getSettings(saveSettings* settings) { this->settings = settings; }

void glScene::updateSettings() {
  backColor.red = (float)settings->colorBack.red / 255;
  backColor.green = (float)settings->colorBack.green / 255;
  backColor.blue = (float)settings->colorBack.blue / 255;

  polColor.red = (float)settings->colorEdges.red / 255;
  polColor.green = (float)settings->colorEdges.green / 255;
  polColor.blue = (float)settings->colorEdges.blue / 255;

  vertColor.red = (float)settings->colorVert.red / 255;
  vertColor.green = (float)settings->colorVert.green / 255;
  vertColor.blue = (float)settings->colorVert.blue / 255;
}

void glScene::getModelData(Model* model) {
  if (model)
    this->Data = model;
  else
    this->Data = NULL;
}

void glScene::affineUpdate() { update(); }
