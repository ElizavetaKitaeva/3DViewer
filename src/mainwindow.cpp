#include "mainwindow.h"

#include <QChar>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>

#include "QtGifImage/qgifimage.h"
#include "ui_mainwindow.h"

using s21::Color;
using s21::Shadow;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QLocale curLocale(QLocale("ru_RU"));
  QLocale::setDefault(curLocale);
  Shadow(40, 0, 5, ui->openFile);
  Shadow(40, 0, 5, ui->settings);
  Shadow(40, 0, 5, ui->rotationDo);
  Shadow(40, 0, 5, ui->translationDo);
  Shadow(40, 0, 5, ui->scaleDo);
  Shadow(40, 0, 5, ui->gifButton);
  Shadow(40, 0, 5, ui->photoButton);  //
  this->settFile = fopen(SETTINGSNAME, "a+");
  parsFileSavedSettings(this->settFile, &(this->settings));
  s21::Color(ui->frame,
             QColor(settings.colorBack.red, settings.colorBack.green,
                    settings.colorBack.blue)
                 .name(),
             "border:2px solid ");
  menu = new Settings(this, &(this->settings));
  connect(this, &MainWindow::applyOldSettings, menu,
          &Settings::applyOldSettings);
  connect(this, &MainWindow::setSettings, ui->openGLWidget,
          &glScene::getSettings);
  connect(menu, &Settings::updateSettings, ui->openGLWidget,
          &glScene::updateSettings);
  connect(this, &MainWindow::affineUpdate, ui->openGLWidget,
          &glScene::affineUpdate);
  emit setSettings(&(this->settings));
  emit applyOldSettings();
}

MainWindow::~MainWindow() {
  fclose(this->settFile);
  free(figure);
  delete ui;
}

void MainWindow::on_openFile_clicked() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Choose .obj file"),
                                                  "../../../../src/Models",
                                                  tr("OBJ FILES (*.obj)"));
  if (!filename.isEmpty()) {
    QStringList filenamesmol = filename.split("/");
    ui->fileNameLine->setText(filenamesmol[filenamesmol.size() - 1]);
    char* fileName = (char*)calloc(256, sizeof(char));
    strcpy(fileName, (filename.toLocal8Bit().constData()));
    if (figure) {
      free(figure->polygons);
      free(figure->vertices);
      free(figure);
      figure = NULL;
    }
    FILE* objFile;
    objFile = fopen(fileName, "rw");
    figure = (Model*)calloc(1, sizeof(Model));
    ParsFiles(objFile, figure);
    ui->verticesLine->setText(QString::number(figure->vertNumber));
    ui->edgesLine->setText(QString::number(figure->polNumber));
    fclose(objFile);
    ui->openGLWidget->getModelData(figure);
    free(fileName);
  }
}

void MainWindow::on_settings_clicked() {
  menu->exec();
  s21::Color(ui->frame,
             QColor(settings.colorBack.red, settings.colorBack.green,
                    settings.colorBack.blue)
                 .name(),
             "border:2px solid ");
}

void MainWindow::on_photoButton_clicked() {
  QImage screenshot = ui->openGLWidget->grabFramebuffer();

  const QString format = "jpeg";
  QString default_path = "images";
  QFileDialog save_dialog(this, tr("Сохранить как"), default_path);
  save_dialog.setAcceptMode(QFileDialog::AcceptSave);
  save_dialog.setFileMode(QFileDialog::AnyFile);
  save_dialog.setDirectory(default_path);
  save_dialog.setDefaultSuffix(format);

  QStringList mime_types;
  const QList<QByteArray> ba_mime_types = QImageWriter::supportedMimeTypes();
  for (const QByteArray& bf : ba_mime_types)
    mime_types.append(QLatin1String(bf));
  save_dialog.setMimeTypeFilters(mime_types);
  save_dialog.selectMimeTypeFilter("image/" + format);

  if (save_dialog.exec() == QDialog::Accepted) {
    const QString fname = save_dialog.selectedFiles().first();
    if (!screenshot.save(fname)) {
      QMessageBox::warning(this, tr("Ошибка"),
                           tr("Невозможно сохранить изображение в \"%1\".")
                               .arg(QDir::toNativeSeparators(fname)));
    }
  }
}

void MainWindow::on_scaleDo_clicked() {
  if (figure) {
    if (ui->scaleXVal->value() != 1 || ui->scaleYVal->value() != 1 ||
        ui->scaleZVal->value() != 1) {
      ScaleTransform(figure->vertices, figure->vertNumber * 3,
                     ui->scaleXVal->value(), ui->scaleYVal->value(),
                     ui->scaleZVal->value());
    }
    emit affineUpdate();
  }
}

void MainWindow::on_translationDo_clicked() {
  if (figure) {
    if (ui->translationXVal->value() || ui->translationYVal->value() ||
        ui->translationZVal->value()) {
      MoveTransform(figure->vertices, figure->vertNumber * 3,
                    ui->translationXVal->value(), ui->translationYVal->value(),
                    ui->translationZVal->value());
    }
    emit affineUpdate();
  }
}

void MainWindow::on_rotationDo_clicked() {
  if (figure) {
    Rotate(figure->vertices, figure->vertNumber * 3, ui->rotationXVal->value(),
           ui->rotationYVal->value(), ui->rotationZVal->value());
    emit affineUpdate();
  }
}

void MainWindow::on_gifButton_clicked() {
  QString filename = QFileDialog::getSaveFileName(
      this, tr("Save File"), "../../../../", tr("(*.gif)"));
  if (!filename.isEmpty()) {
    QGifImage gif(ui->openGLWidget->grab().size());
    gif.setDefaultDelay(100);
    for (int i = 0; i < 50; i++) {
      on_scaleDo_clicked();
      on_translationDo_clicked();
      on_rotationDo_clicked();
      QImage screenshot = ui->openGLWidget->grabFramebuffer();
      gif.addFrame(screenshot);
    }
    gif.save(filename);
  }
}
