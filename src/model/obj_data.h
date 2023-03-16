#ifndef SRC_MODEL_OBJ_DATA_H_
#define SRC_MODEL_OBJ_DATA_H_

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../common/viewer_exception.h"
#include "edge.h"
#include "vertex.h"

struct Borders {
  double z_max, z_min;
};

class ObjData {
 public:
  ObjData();

  void OpenFile(std::string path);
  std::string& GetModel();
  std::vector<Vertex>& GetVertices();
  std::vector<Edge>& GetFacets();
  Borders& GetBorders();
  void Clear();

 private:
  std::string model_;
  std::vector<Vertex> vertices_;
  std::vector<Edge> facets_;
  Borders borders_;

  void ParseVertex(std::string line);
  void ParseFacet(std::string line);
};

#endif  // SRC_MODEL_OBJ_DATA_H_
