#include "glview.h"

GlView::GlView(QWidget* parent)
    : QOpenGLWidget(parent), settings_(&Settings::GetInstance()), p_{} {
  connect(&timer_, SIGNAL(timeout()), this, SLOT(update()));
  timer_.start(100);
  InitializePerspective();
}

void GlView::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GlView::paintGL() {
  glClearColor(settings_->Value("bg_color_r") / 255.0,
               settings_->Value("bg_color_g") / 255.0,
               settings_->Value("bg_color_b") / 255.0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (settings_->Value("projection_type")) {
    p_.scale = 4;
    glFrustum(-1, 1, -1, 1, 1, qPow(3000, 2));
  } else {
    if (p_.scale == 4) {
      p_.scale = 1;
    }
    GLfloat ratio = (GLfloat)600 / (GLfloat)600;
    glOrtho(-2.0 / ratio, 2.0 / ratio, -2.0, 2.0, -50.0, 50.0);
  }
  glScalef(p_.scale, p_.scale, p_.scale);
  glTranslatef(p_.x_pos, 0, 0);
  glTranslatef(0, p_.y_pos, 0);
  glTranslatef(0, 0, p_.z_pos);
  glRotatef(p_.x_rot, 1.0f, 0.0f, 0.0f);
  glRotatef(p_.y_rot, 0.0f, 1.0f, 0.0f);
  glRotatef(p_.z_rot, 0.0f, 0.0f, 1.0f);
  if (settings_->Value("grid_on")) {
    DrawAxis();
    DrawGrid(100.0, 100.0, 1.0);
  }
  DrawObject();
}

void GlView::DrawObject() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0, gl_viewer->GetVertices().data());
  if (settings_->Value("vertex_shape") > 0) {
    if (settings_->Value("vertex_shape") == 1) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }
    glPointSize(settings_->Value("vertex_size"));
    glColor3d(settings_->Value("vertex_color_r") / 255.0,
              settings_->Value("vertex_color_g") / 255.0,
              settings_->Value("vertex_color_b") / 255.0);
    glDrawArrays(GL_POINTS, 0, gl_viewer->GetVertices().size());
  }
  if (settings_->Value("edge_type") == 0) {
    glDisable(GL_LINE_STIPPLE);
  } else {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1111);
  }
  glLineWidth(settings_->Value("edge_width"));
  glColor3d(settings_->Value("edge_color_r") / 255.0,
            settings_->Value("edge_color_g") / 255.0,
            settings_->Value("edge_color_b") / 255.0);
  glDrawElements(GL_LINES, gl_viewer->GetFacets().size() * 2, GL_UNSIGNED_INT,
                 gl_viewer->GetFacets().data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GlView::InitializePerspective() {
  p_.x_rot = 4;
  p_.y_rot = 0;
  p_.z_rot = 0;
  p_.x_pos = 0;
  p_.y_pos = 0;
  p_.z_pos = -4;
  p_.scale = 1;
}

void GlView::DrawGrid(float ax, float ay, float step) {
  float cx = ax / 2;
  float cy = ay / 2;
  glLineStipple(1, 0xAAAA);
  glStencilFunc(GL_NOTEQUAL, 1, 255);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_TRIANGLE_FAN);
  glColor4d(1, 1, 1, 0.3);
  for (int ix = -cx; ix <= cx; ix += step) {
    glBegin(GL_LINE_STRIP);
    glVertex3f(ix, 0, cy);
    glVertex3f(ix, 0, -cy);
    glEnd();
  }
  for (int iy = -cy; iy <= cy; iy += step) {
    glBegin(GL_LINE_STRIP);
    glVertex3f(cx, 0, iy);
    glVertex3f(-cx, 0, iy);
    glEnd();
  }
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_STENCIL_TEST);
}

void GlView::DrawAxis() {
  glLineWidth(3.0f);
  glColor4f(1.0f, 0.0f, 0.0f, 0.3);
  glBegin(GL_LINES);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-1.0f, 0.0f, 0.0f);
  glEnd();
  glColor4f(0.0f, 1.0f, 0.0f, 0.3);
  glBegin(GL_LINES);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, -1.0f, 0.0f);
  glColor4f(0.0f, 0.0f, 1.0f, 0.3);
  glVertex3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, -1.0f);
  glEnd();
}

void GlView::mousePressEvent(QMouseEvent* m) { p_.mouse_pos_ = m->pos(); }

void GlView::mouseMoveEvent(QMouseEvent* m) {
  double move_sense = 100;
  static int cur_x = 0;
  static int cur_y = 0;
  if (!cur_x and !cur_y) {
    cur_x = m->pos().x();
    cur_y = m->pos().y();
  }
  if (abs(m->pos().x() - cur_x) < move_sense and
      abs(m->pos().y() - cur_y) < move_sense) {
    if (m->buttons() & Qt::LeftButton) {
      p_.x_pos += 0.01 / p_.scale * (m->pos().x() - p_.mouse_pos_.x());
      p_.y_pos += -0.01 / p_.scale * (m->pos().y() - p_.mouse_pos_.y());
    } else {
      p_.x_rot += 1 / M_PI * (m->pos().y() - p_.mouse_pos_.y());
      p_.y_rot += 1 / M_PI * (m->pos().x() - p_.mouse_pos_.x());
      p_.z_rot += 0.01 / M_PI * (sin(p_.x_rot));
    }
  }

  p_.mouse_pos_ = m->pos();
  cur_x = m->pos().x();
  cur_y = m->pos().y();
  update();
}

void GlView::wheelEvent(QWheelEvent* e) {
  if (settings_->Value("projection_type")) {
    int angle = e->angleDelta().y();
    if (angle > 0)
      p_.z_pos += 0.1;
    else if (angle < 0)
      p_.z_pos -= 0.1;
  } else {
    int angle = e->angleDelta().y();
    if (angle > 0)
      p_.scale += 0.1;
    else if (angle < 0 and p_.scale > 0.2)
      p_.scale -= 0.1;
  }
  update();
}
