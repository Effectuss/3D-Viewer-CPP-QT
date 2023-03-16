#ifndef SRC_MODEL_FACADE_H_
#define SRC_MODEL_FACADE_H_

#include <string>
#include <vector>

#include "../common/settings.h"
#include "../model/affine.h"
#include "../model/edge.h"
#include "../model/obj_data.h"
#include "../model/vertex.h"

class Controller {
 public:
  explicit Controller(ObjData* obj, Affine* affine, CareTaker* caretaker);
  ~Controller();

  std::string& GetModel();
  std::vector<Vertex>& GetVertices();
  std::vector<Edge>& GetFacets();
  Borders& GetBorders();
  void SetModel(std::string path);
  void MoveX(double x);
  void MoveY(double y);
  void MoveZ(double z);
  void RotateX(double angle);
  void RotateY(double angle);
  void RotateZ(double angle);
  void Scale(double ratio);
  void Clear();
  void SavePosition();
  void ResetPosition();

 private:
  void ScaleToFrame();

  ObjData* obj_;
  Affine* affine_;
  CareTaker* caretaker_;
};

#endif  // SRC_MODEL_FACADE_H_
