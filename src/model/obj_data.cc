#include "obj_data.h"

ObjData::ObjData() : model_(), vertices_(), facets_(), borders_() {}

std::string& ObjData::GetModel() { return model_; }

std::vector<Vertex>& ObjData::GetVertices() { return vertices_; }

std::vector<Edge>& ObjData::GetFacets() { return facets_; }

Borders& ObjData::GetBorders() { return borders_; }

void ObjData::OpenFile(std::string path) {
  std::ifstream file(path);
  if (!file) throw ViewerException("InputError: File not load");
  if (path.substr(path.size() - 4, 4) != ".obj")
    throw ViewerException("InputError: Incorrect file extension");
  Clear();
  size_t idx = path.find_last_of('/');
  model_ = path.substr(idx + 1, path.size() - idx);
  borders_.z_max = -INFINITY;
  borders_.z_min = INFINITY;
  while (file) {
    std::string line;
    getline(file, line);
    if (line.substr(0, 2) == "v ") {
      ParseVertex(line);
    } else if (line.substr(0, 2) == "f ") {
      ParseFacet(line);
    }
  }
  file.close();
}

void ObjData::ParseVertex(std::string line) {
  std::istringstream v(line.substr(2));
  double x, y, z;
  v >> x >> y >> z;
  vertices_.emplace_back(x, y, z);
  borders_.z_max = std::max(z, borders_.z_max);
  borders_.z_min = std::min(z, borders_.z_min);
}

void ObjData::ParseFacet(std::string line) {
  size_t a, b, first;
  size_t idx = line.find(' ');
  first = a = std::stoi(line.substr(idx + 1), nullptr) - 1;
  idx = line.find(' ', idx + 1);
  while (idx != std::string::npos) {
    if (idx + 1 < line.size() && std::isdigit(line.at(idx + 1))) {
      b = std::stoi(line.substr(idx + 1), nullptr) - 1;
    }
    facets_.emplace_back(a, b);
    a = b;
    idx = line.find(' ', idx + 1);
  }
  facets_.emplace_back(a, first);
}

void ObjData::Clear() {
  model_.clear();
  vertices_.clear();
  facets_.clear();
}
