#include "controller.h"

Controller::Controller(ObjData* obj, Affine* affine, CareTaker* caretaker)
    : obj_(obj), affine_(affine), caretaker_(caretaker) {}

Controller::~Controller() {}

std::string& Controller::GetModel() { return obj_->GetModel(); }

std::vector<Vertex>& Controller::GetVertices() {
  return affine_->GetVertices();
}

std::vector<Edge>& Controller::GetFacets() { return obj_->GetFacets(); }

Borders& Controller::GetBorders() { return obj_->GetBorders(); }

void Controller::SetModel(std::string path) {
  Clear();
  obj_->OpenFile(path);
  affine_->SetVertices(obj_->GetVertices());
  ScaleToFrame();
  SavePosition();
}

void Controller::MoveX(double x) { affine_->MoveX(x); }

void Controller::MoveY(double y) { affine_->MoveY(y); }

void Controller::MoveZ(double z) { affine_->MoveZ(z); }

void Controller::RotateX(double angle) { affine_->RotateX(angle); }

void Controller::RotateY(double angle) { affine_->RotateY(angle); }

void Controller::RotateZ(double angle) { affine_->RotateZ(angle); }

void Controller::Scale(double ratio) { affine_->Scale(ratio); }

void Controller::Clear() {
  caretaker_->Clear();
  affine_->Clear();
  obj_->Clear();
}

void Controller::SavePosition() { caretaker_->Save(); }

void Controller::ResetPosition() { caretaker_->Undo(); }

void Controller::ScaleToFrame() {
  affine_->ScaleToFrame(GetBorders().z_max - GetBorders().z_min);
}
