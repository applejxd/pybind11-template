#include <pybind11/pybind11.h>

#include "bind_eigen.hpp"

// 引数の１つ目はモジュール名
PYBIND11_MODULE(bind, m) {
  // docstring
  m.doc() = "binding for C++ libraries";

  bind_eigen::bind_eigen(m);
}