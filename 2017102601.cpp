#include <iostream>

template <int v>
struct int_wrapper {
  static constexpr int value = v;
};

template <class T>
auto get_value() {
  return T::value;
}

int main() {
  std::cout << get_value<int_wrapper<1>>() << std::endl;
}
