#ifndef SRC_MODEL_EDGE_H_
#define SRC_MODEL_EDGE_H_

#include <cstdint>

class Edge {
 public:
  Edge(uint32_t a, uint32_t b) : a_(a), b_(b) {}
  uint32_t GetA() { return this->a_; }
  uint32_t GetB() { return this->b_; }

 private:
  uint32_t a_;
  uint32_t b_;
};

#endif  // SRC_MODEL_EDGE_H_
