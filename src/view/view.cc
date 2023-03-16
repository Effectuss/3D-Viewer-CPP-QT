#include "view.h"

#include "ui_view.h"

View::View(Controller *controller, QWidget *parent)
    : QMainWindow(parent),
      settings_(&Settings::GetInstance()),
      ui_(new Ui::View),
      controller_(controller) {
  ui_->setupUi(this);
  this->setWindowTitle("3DViewer v2.0");
  ConnectSlots();
  InitializeUi();
  InitializeMenu();
  LoadSettings();
  ui_->glWindow->gl_viewer = controller_;
}

View::~View() { delete ui_; }

void View::ConnectSlots() {
  connect(ui_->load_file, SIGNAL(clicked()), this, SLOT(LoadFileClick()));
  connect(ui_->slider_move_x, SIGNAL(valueChanged(int)), this,
          SLOT(SliderMoveX(int)));
  connect(ui_->slider_move_y, SIGNAL(valueChanged(int)), this,
          SLOT(SliderMoveY(int)));
  connect(ui_->slider_move_z, SIGNAL(valueChanged(int)), this,
          SLOT(SliderMoveZ(int)));
  connect(ui_->translate, SIGNAL(clicked()), this, SLOT(TranslateClick()));
  connect(ui_->slider_rot_x, SIGNAL(valueChanged(int)), this,
          SLOT(SliderRotateX(int)));
  connect(ui_->slider_rot_y, SIGNAL(valueChanged(int)), this,
          SLOT(SliderRotateY(int)));
  connect(ui_->slider_rot_z, SIGNAL(valueChanged(int)), this,
          SLOT(SliderRotateZ(int)));
  connect(ui_->rotate, SIGNAL(clicked()), this, SLOT(RotateClick()));
  connect(ui_->slider_scale, SIGNAL(valueChanged(int)), this,
          SLOT(SliderScale(int)));
  connect(ui_->scale, SIGNAL(clicked()), this, SLOT(ScaleClick()));
  connect(ui_->settings, SIGNAL(clicked()), this, SLOT(SettingsClick()));
  connect(ui_->screenshot, SIGNAL(clicked()), this, SLOT(ScreenshotClick()));
  connect(ui_->gif, SIGNAL(clicked()), this, SLOT(GifClick()));
  connect(ui_->save_pos, SIGNAL(clicked()), this, SLOT(SavePosition()));
  connect(ui_->reset_pos, SIGNAL(clicked()), this, SLOT(ResetPosition()));
  connect(ui_->vertex_size_decr, SIGNAL(clicked()), this,
          SLOT(VertexSizeDecrement()));
  connect(ui_->vertex_size_incr, SIGNAL(clicked()), this,
          SLOT(VertexSizeIncrement()));
  connect(ui_->edge_width_decr, SIGNAL(clicked()), this,
          SLOT(EdgeWidthDecrement()));
  connect(ui_->edge_width_incr, SIGNAL(clicked()), this,
          SLOT(EdgeWidthIncrement()));
  connect(ui_->vertex_color, SIGNAL(clicked()), this, SLOT(VertexColorClick()));
  connect(ui_->edge_color, SIGNAL(clicked()), this, SLOT(EdgeColorClick()));
  connect(ui_->bg_color, SIGNAL(clicked()), this, SLOT(BackColorClick()));
  connect(ui_->set_default, SIGNAL(clicked()), this, SLOT(DefaultClick()));
  connect(ui_->set_cancel, SIGNAL(clicked()), this, SLOT(CancelClick()));
  connect(ui_->set_apply, SIGNAL(clicked()), this, SLOT(ApplyClick()));
  connect(ui_->grid_on, SIGNAL(toggled(bool)), this, SLOT(SetGrid()));
}

void View::LoadFileClick() {
  QString path = QFileDialog::getOpenFileName(this, ("Open .obj file"),
                                              QDir::homePath(), "*.obj");
  try {
    controller_->SetModel(path.toStdString());
    InitializeUi();
    ui_->label_file->setText(QString::fromStdString(controller_->GetModel()));
    ui_->cnt_vertices->setText(
        QString::number(controller_->GetVertices().size()));
    ui_->cnt_edges->setText(QString::number(controller_->GetFacets().size()));
  } catch (std::exception &err) {
    InitializeUi();
    controller_->Clear();
    ui_->err_display->setText(err.what());
  }
}

void View::InitializeUi() {
  ui_->label_file->setText("-");
  ui_->cnt_vertices->setText("0");
  ui_->cnt_edges->setText("0");
  ui_->spin_move_x->setPrefix("x  ");
  ui_->spin_move_y->setPrefix("y  ");
  ui_->spin_move_z->setPrefix("z  ");
  ui_->spin_rot_x->setPrefix("x  ");
  ui_->spin_rot_y->setPrefix("y  ");
  ui_->spin_rot_z->setPrefix("z  ");
  ui_->spin_move_x->setValue(0);
  ui_->spin_move_y->setValue(0);
  ui_->spin_move_z->setValue(0);
  ui_->spin_rot_x->setValue(0);
  ui_->spin_rot_y->setValue(0);
  ui_->spin_rot_z->setValue(0);
  ui_->spin_scale->setValue(1);
  ui_->slider_move_x->setValue(0);
  ui_->slider_move_y->setValue(0);
  ui_->slider_move_z->setValue(0);
  ui_->slider_rot_x->setValue(0);
  ui_->slider_rot_y->setValue(0);
  ui_->slider_rot_z->setValue(0);
  ui_->slider_scale->setValue(1);
  ui_->err_display->setText("");
}

void View::GlUpdate() { ui_->glWindow->update(); }

void View::SliderMoveX(int value) {
  if (ui_->spin_move_x->value() != value) {
    controller_->MoveX((ui_->spin_move_x->value() - value) / -100.0);
    ui_->spin_move_x->setValue(value);
  }
  if (value == 0) {
    ui_->slider_move_x->setValue(0);
  }
  ui_->glWindow->update();
}

void View::SliderMoveY(int value) {
  if (ui_->spin_move_y->value() != value) {
    controller_->MoveY((ui_->spin_move_y->value() - value) / -100.0);
    ui_->spin_move_y->setValue(value);
  }
  if (value == 0) {
    ui_->slider_move_y->setValue(0);
  }
  ui_->glWindow->update();
}

void View::SliderMoveZ(int value) {
  if (ui_->spin_move_z->value() != value) {
    controller_->MoveZ((ui_->spin_move_z->value() - value) / -100.0);
    ui_->spin_move_z->setValue(value);
  }
  if (value == 0) {
    ui_->slider_move_z->setValue(0);
  }
  ui_->glWindow->update();
}

void View::TranslateClick() {
  ui_->slider_move_x->setSliderPosition(ui_->spin_move_x->value());
  controller_->MoveX(ui_->spin_move_x->value() / 100.0);

  ui_->slider_move_y->setSliderPosition(ui_->spin_move_y->value());
  controller_->MoveY(ui_->spin_move_y->value() / 100.0);

  ui_->slider_move_z->setSliderPosition(ui_->spin_move_z->value());
  controller_->MoveZ(ui_->spin_move_z->value() / 100.0);

  ui_->glWindow->update();
}

void View::SliderRotateX(int value) {
  if (ui_->spin_rot_x->value() != value) {
    controller_->RotateX((ui_->spin_rot_x->value() - value) / -100.0);
    ui_->spin_rot_x->setValue(value);
  }
  if (value == 0) {
    ui_->slider_rot_x->setValue(0);
  }
  ui_->glWindow->update();
}

void View::SliderRotateY(int value) {
  if (ui_->spin_rot_y->value() != value) {
    controller_->RotateY((ui_->spin_rot_y->value() - value) / -100.0);
    ui_->spin_rot_y->setValue(value);
  }
  if (value == 0) {
    ui_->slider_rot_y->setValue(0);
  }
  ui_->glWindow->update();
}

void View::SliderRotateZ(int value) {
  if (ui_->spin_rot_z->value() != value) {
    controller_->RotateZ((ui_->spin_rot_z->value() - value) / -100.0);
    ui_->spin_rot_z->setValue(value);
  }
  if (value == 0) {
    ui_->slider_rot_z->setValue(0);
  }
  ui_->glWindow->update();
}

void View::RotateClick() {
  ui_->slider_rot_x->setSliderPosition(ui_->spin_rot_x->value());
  controller_->RotateX(ui_->spin_rot_x->value() / 100.0);

  ui_->slider_rot_y->setSliderPosition(ui_->spin_rot_y->value());
  controller_->RotateY(ui_->spin_rot_y->value() / 100.0);

  ui_->slider_rot_z->setSliderPosition(ui_->spin_rot_z->value());
  controller_->RotateZ(ui_->spin_rot_z->value() / 100.0);

  ui_->glWindow->update();
}

void View::SliderScale(int value) {
  if (ui_->spin_scale->value() != value && ui_->spin_scale->value() < value) {
    ui_->spin_scale->setValue(value);
    controller_->Scale(1.1);
  }
  if (ui_->spin_scale->value() != value && ui_->spin_scale->value() > value) {
    ui_->spin_scale->setValue(value);
    controller_->Scale(0.9);
  }
  if (value == 0) {
    ui_->slider_scale->setValue(0);
  }
  ui_->glWindow->update();
}

void View::ScaleClick() {
  ui_->slider_scale->setSliderPosition(ui_->spin_scale->value());
  if (ui_->spin_scale->value() > 0)
    controller_->Scale(1.1 * ui_->spin_scale->value());
  if (ui_->spin_scale->value() < 0)
    controller_->Scale(-0.9 / ui_->spin_scale->value());
  ui_->glWindow->update();
}

void View::SettingsClick() {
  if (this->width() == this->minimumWidth()) {
    this->resize(this->maximumWidth(), this->height());
  } else {
    this->resize(this->minimumWidth(), this->height());
  }
}

void View::ScreenshotClick() {
  QString path = NULL;
  path = QFileDialog::getSaveFileName(this, NULL, NULL,
                                      "JPEG (*.jpeg) ;; BMP (*.bmp)");
  if (!path.isNull()) ui_->glWindow->grabFramebuffer().save(path, NULL, 100);
}

void View::GifClick() {
  gif_ = new QGifImage(QSize(640, 480));
  gif_->setDefaultDelay(100);
  frame_ = new QImage;
  timer_ = new QTimer(0);
  time_ = 0;
  connect(timer_, SIGNAL(timeout()), this, SLOT(SaveGif()));
  timer_->setInterval(100);
  timer_->start(100);
}

void View::SaveGif() {
  ++time_;
  *frame_ = ui_->glWindow->grabFramebuffer();
  *frame_ =
      frame_->scaled(640, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  gif_->addFrame(*frame_, 100);
  if (time_ == 60) {
    timer_->stop();
    gif_path_ = NULL;
    gif_path_ = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    if (!gif_path_.isNull()) gif_->save(gif_path_);
  }
}

void View::SavePosition() { controller_->SavePosition(); }

void View::ResetPosition() {
  controller_->ResetPosition();
  ui_->glWindow->update();
}

void View::LoadSettings() {
  ui_->vertex_color_r->setValue(settings_->Value("vertex_color_r"));
  ui_->vertex_color_g->setValue(settings_->Value("vertex_color_g"));
  ui_->vertex_color_b->setValue(settings_->Value("vertex_color_b"));
  ui_->vertex_size->setValue(settings_->Value("vertex_size"));
  ui_->vertex_shape->setCurrentIndex(settings_->Value("vertex_shape"));
  ui_->edge_color_r->setValue(settings_->Value("edge_color_r"));
  ui_->edge_color_g->setValue(settings_->Value("edge_color_g"));
  ui_->edge_color_b->setValue(settings_->Value("edge_color_b"));
  ui_->edge_width->setValue(settings_->Value("edge_width"));
  ui_->edge_type->setCurrentIndex(settings_->Value("edge_type"));
  ui_->bg_color_r->setValue(settings_->Value("bg_color_r"));
  ui_->bg_color_g->setValue(settings_->Value("bg_color_g"));
  ui_->bg_color_b->setValue(settings_->Value("bg_color_b"));
  ui_->projection_type->setCurrentIndex(settings_->Value("projection_type"));
  ui_->grid_off->setChecked(!settings_->Value("grid_on"));
}

void View::InitializeMenu() {
  ui_->vertex_color_r->setSuffix(" R");
  ui_->vertex_color_g->setSuffix(" G");
  ui_->vertex_color_b->setSuffix(" B");
  ui_->edge_color_r->setSuffix(" R");
  ui_->edge_color_g->setSuffix(" G");
  ui_->edge_color_b->setSuffix(" B");
  ui_->bg_color_r->setSuffix(" R");
  ui_->bg_color_g->setSuffix(" G");
  ui_->bg_color_b->setSuffix(" B");
}

void View::SaveSettings() {
  settings_->SetValue("vertex_color_r", ui_->vertex_color_r->value());
  settings_->SetValue("vertex_color_g", ui_->vertex_color_g->value());
  settings_->SetValue("vertex_color_b", ui_->vertex_color_b->value());
  settings_->SetValue("vertex_size", ui_->vertex_size->value());
  settings_->SetValue("vertex_shape", ui_->vertex_shape->currentIndex());
  settings_->SetValue("edge_color_r", ui_->edge_color_r->value());
  settings_->SetValue("edge_color_g", ui_->edge_color_g->value());
  settings_->SetValue("edge_color_b", ui_->edge_color_b->value());
  settings_->SetValue("edge_width", ui_->edge_width->value());
  settings_->SetValue("edge_type", ui_->edge_type->currentIndex());
  settings_->SetValue("bg_color_r", ui_->bg_color_r->value());
  settings_->SetValue("bg_color_g", ui_->bg_color_g->value());
  settings_->SetValue("bg_color_b", ui_->bg_color_b->value());
  settings_->SetValue("projection_type", ui_->projection_type->currentIndex());
}

void View::VertexSizeDecrement() {
  if (ui_->vertex_size->value() > 1) {
    ui_->vertex_size->setValue(ui_->vertex_size->value() - 1);
  }
}

void View::VertexSizeIncrement() {
  if (ui_->vertex_size->value() < 10) {
    ui_->vertex_size->setValue(ui_->vertex_size->value() + 1);
  }
}

void View::EdgeWidthDecrement() {
  if (ui_->edge_width->value() > 1) {
    ui_->edge_width->setValue(ui_->edge_width->value() - 1);
  }
}

void View::EdgeWidthIncrement() {
  if (ui_->edge_width->value() < 10) {
    ui_->edge_width->setValue(ui_->edge_width->value() + 1);
  }
}

void View::CancelClick() { hide(); }

void View::DefaultClick() {
  settings_->SetDefaultAllValues();
  LoadSettings();
}

void View::ApplyClick() { SaveSettings(); }

void View::VertexColorClick() {
  QColor vertex_color = QColorDialog::getColor(QColor(76, 194, 255, 255), this,
                                               "Set vertex color");
  if (vertex_color.isValid()) {
    ui_->vertex_color_r->setValue(vertex_color.red());
    ui_->vertex_color_g->setValue(vertex_color.green());
    ui_->vertex_color_b->setValue(vertex_color.blue());
  }
}

void View::EdgeColorClick() {
  QColor edge_color =
      QColorDialog::getColor(QColor(76, 194, 255, 255), this, "Set edge color");
  if (edge_color.isValid()) {
    ui_->edge_color_r->setValue(edge_color.red());
    ui_->edge_color_g->setValue(edge_color.green());
    ui_->edge_color_b->setValue(edge_color.blue());
  }
}

void View::BackColorClick() {
  QColor bg_color = QColorDialog::getColor(QColor(39, 39, 39, 255), this,
                                           "Set background color");
  if (bg_color.isValid()) {
    ui_->bg_color_r->setValue(bg_color.red());
    ui_->bg_color_g->setValue(bg_color.green());
    ui_->bg_color_b->setValue(bg_color.blue());
  }
}

void View::SetGrid() {
  settings_->SetValue("grid_on", ui_->grid_on->isChecked());
}
