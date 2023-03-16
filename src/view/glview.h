#ifndef SRC_VIEW_GLVIEW_H_
#define SRC_VIEW_GLVIEW_H_

#define GL_SILENCE_DEPRECATION
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>

#elif __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWheelEvent>

#include "../controller/controller.h"

struct Perspective {
  double x_pos, y_pos, z_pos, x_rot, y_rot, z_rot, scale;
  QPoint mouse_pos_;
};

class GlView : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit GlView(QWidget *parent = nullptr);
  Controller *gl_viewer;

 private:
  Settings *settings_;
  Perspective p_;
  QTimer timer_;

  void initializeGL() override;
  void paintGL() override;
  void DrawObject();
  void InitializePerspective();
  void DrawGrid(float ax, float ay, float step);
  void DrawAxis();
  void mousePressEvent(QMouseEvent *m) override;
  void mouseMoveEvent(QMouseEvent *m) override;
  void wheelEvent(QWheelEvent *e) override;
};

#endif  // SRC_VIEW_GLVIEW_H_
