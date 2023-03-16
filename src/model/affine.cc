#include "affine.h"

Affine::Affine() : update_{} {}

std::vector<Vertex>& Affine::GetVertices() { return update_; }

void Affine::SetVertices(std::vector<Vertex> vertices) { update_ = vertices; }

void Affine::MoveX(double x) {
  for (size_t i = 0; i < update_.size(); ++i) {
    update_[i].SetX(update_[i].GetX() + x);
  }
}

void Affine::MoveY(double y) {
  for (size_t i = 0; i < update_.size(); ++i) {
    update_[i].SetY(update_[i].GetY() + y);
  }
}

void Affine::MoveZ(double z) {
  for (size_t i = 0; i < update_.size(); ++i) {
    update_[i].SetZ(update_[i].GetZ() + z);
  }
}

void Affine::RotateX(double angle) {
  for (size_t i = 0; i < update_.size(); ++i) {
    double y = update_[i].GetY();
    double z = update_[i].GetZ();
    update_[i].SetY(y * cos(angle) - z * sin(angle));
    update_[i].SetZ(y * sin(angle) + z * cos(angle));
  }
}

void Affine::RotateY(double angle) {
  for (size_t i = 0; i < update_.size(); ++i) {
    double x = update_[i].GetX();
    double z = update_[i].GetZ();
    update_[i].SetX(x * cos(angle) + z * sin(angle));
    update_[i].SetZ(-x * sin(angle) + z * cos(angle));
  }
}

void Affine::RotateZ(double angle) {
  for (size_t i = 0; i < update_.size(); ++i) {
    double x = update_[i].GetX();
    double y = update_[i].GetY();
    update_[i].SetX(x * cos(angle) - y * sin(angle));
    update_[i].SetY(x * sin(angle) + y * cos(angle));
  }
}

void Affine::Scale(double ratio) {
  for (size_t i = 0; i < update_.size(); ++i) {
    if (ratio) {
      update_[i].SetX(update_[i].GetX() * ratio);
      update_[i].SetY(update_[i].GetY() * ratio);
      update_[i].SetZ(update_[i].GetZ() * ratio);
    }
  }
}

void Affine::Clear() { update_.clear(); }

void Affine::SetMemento(Memento* const m) { update_ = m->GetState(); }

Memento* Affine::CreateMemento() { return new Memento(update_); }

void Affine::ScaleToFrame(double k) {
  while (k > 6) {
    Scale(0.7);
    k *= 0.7;
  }
}
