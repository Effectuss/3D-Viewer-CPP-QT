#ifndef SRC_MODEL_MEMENTO_H
#define SRC_MODEL_MEMENTO_H

#include <vector>

#include "vertex.h"

class Affine;

class Memento {
 private:
  friend class Affine;

  Memento(const std::vector<Vertex> &vertices);
  std::vector<Vertex> GetState();

 private:
  std::vector<Vertex> vertices_;
};

class CareTaker {
 public:
  CareTaker(Affine *const o);
  ~CareTaker();

  void Save();
  void Undo();
  void Clear();

 private:
  Affine *originator_;
  std::vector<Memento *> history_;
};

#endif  // SRC_MODEL_MEMENTO_H
