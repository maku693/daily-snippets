#include <algorithm>
#include <iostream>
#include <vector>
#include "gsl/span"

template <class Range>
void print_range(const Range& range) {
  for (const auto& i : range) {
    std::cout << i << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::vector<int> v{3, 2, 1};
  nonstd::span<int> s(v);

  print_range(v);
  print_range(s);

  std::sort(s.begin(), s.end());

  print_range(v);
  print_range(s);
}
