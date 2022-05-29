#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <cmath>
#include <memory>

class Graph {
 public:
  std::vector<int> operator()(int width, int height) const {
    std::vector<int> output(width);
    for (int i = 0; i < width; ++i) {
      float v = 0;
      v += 0.1f * std::sin((i + *shift) * 0.1f);        // NOLINT
      v += 0.2f * std::sin((i + *shift + 10) * 0.15f);  // NOLINT
      v += 0.1f * std::sin((i + *shift) * 0.03f);       // NOLINT
      v *= height;                                // NOLINT
      v += 0.5f * height;                         // NOLINT
      output[i] = static_cast<int>(v);
    }
    return output;
  }
  int shiftt;
  std::shared_ptr<size_t> shift = std::make_shared<size_t>();
};

#endif
