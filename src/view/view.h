#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QThread>
#include <QTimer>

#include "../common/viewer_exception.h"
#include "controller/controller.h"
#include "glview.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(Controller *viewer, QWidget *parent = nullptr);
  ~View();

 private slots:
  void LoadFileClick();
  void SliderMoveX(int value);
  void SliderMoveY(int value);
  void SliderMoveZ(int value);
  void TranslateClick();
  void SliderRotateX(int value);
  void SliderRotateY(int value);
  void SliderRotateZ(int value);
  void RotateClick();
  void SliderScale(int value);
  void ScaleClick();
  void SettingsClick();
  void GlUpdate();
  void ScreenshotClick();
  void GifClick();
  void SaveGif();
  void SavePosition();
  void ResetPosition();
  void VertexSizeDecrement();
  void VertexSizeIncrement();
  void EdgeWidthDecrement();
  void EdgeWidthIncrement();
  void CancelClick();
  void DefaultClick();
  void ApplyClick();
  void VertexColorClick();
  void EdgeColorClick();
  void BackColorClick();
  void SetGrid();

 private:
  void LoadSettings();
  void ConnectSlots();
  void InitializeUi();
  void SaveSettings();
  void InitializeMenu();

  Settings *settings_;
  Ui::View *ui_;
  Controller *controller_;
  QGifImage *gif_;
  QImage *frame_;
  QTimer *timer_;
  size_t time_;
  QString gif_path_;
};

#endif  // SRC_VIEW_VIEW_H_
