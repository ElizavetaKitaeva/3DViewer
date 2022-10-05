#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSvg>

#include "settings.h"

extern "C" {
#include "affine.h"
#include "fileReader.h"
#include "parsSavedSettings.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private slots:
  void on_openFile_clicked();
  void on_settings_clicked();
  void on_photoButton_clicked();

  void on_scaleDo_clicked();

  void on_translationDo_clicked();

  void on_rotationDo_clicked();

  void on_gifButton_clicked();

 signals:
  void fileSetter(FILE* s);
  void applyOldSettings();
  void setSettings(saveSettings* settings);
  void affineUpdate();

 private:
  Ui::MainWindow* ui;
  Settings* menu = NULL;
  saveSettings settings = {0,         0,        1, 0, 1, {255, 255, 255},
                           {0, 0, 0}, {0, 0, 0}};
  FILE* settFile = NULL;
  Model* figure = NULL;
};
#endif  // MAINWINDOW_H
