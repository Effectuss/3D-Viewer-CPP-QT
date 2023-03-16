#ifndef SRC_MODEL_AFFINE_H_
#define SRC_MODEL_AFFINE_H_

#include <cmath>
#include <vector>

#include "memento.h"
#include "vertex.h"

class Affine {
 public:
  Affine();

  std::vector<Vertex>& GetVertices();
  void SetVertices(std::vector<Vertex> vertices);
  void MoveX(double x);
  void MoveY(double y);
  void MoveZ(double z);
  void RotateX(double angle);
  void RotateY(double angle);
  void RotateZ(double angle);
  void Scale(double ratio);
  void Clear();
  void SetMemento(Memento* const m);
  Memento* CreateMemento();
  void ScaleToFrame(double k);

 private:
  std::vector<Vertex> update_;
};

#endif  // SRC_MODEL_AFFINE_H_
