#include "memento.h"

#include "affine.h"

Memento::Memento(const std::vector<Vertex> &vertices) : vertices_(vertices) {}

std::vector<Vertex> Memento::GetState() { return vertices_; }

CareTaker::CareTaker(Affine *const o) : originator_(o) {}

CareTaker::~CareTaker() { Clear(); }

void CareTaker::Save() { history_.push_back(originator_->CreateMemento()); }

void CareTaker::Undo() {
  if (history_.empty()) {
    return;
  }
  Memento *m = history_.back();
  originator_->SetMemento(m);
  if (history_.size() > 1) {
    history_.pop_back();
    delete m;
  }
}

void CareTaker::Clear() {
  for (unsigned int i = 0; i < history_.size(); i++) {
    delete history_.at(i);
  }
  history_.clear();
}
