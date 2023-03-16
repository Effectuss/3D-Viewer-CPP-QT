#ifndef SRC_MODEL_VERTEX_H_
#define SRC_MODEL_VERTEX_H_

class Vertex {
 public:
  Vertex(double x, double y, double z) : x_(x), y_(y), z_(z) {}

  double GetX() { return x_; }
  double GetY() { return y_; }
  double GetZ() { return z_; }
  void SetX(double x) { x_ = x; }
  void SetY(double y) { y_ = y; }
  void SetZ(double z) { z_ = z; }

 private:
  double x_;
  double y_;
  double z_;
};

#endif  // SRC_MODEL_VERTEX_H_
