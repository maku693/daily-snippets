#include <iostream>
#include <set>

int main() {
  std::set<int> s {3, 2, 1};
  for (auto v : s) {
    std::cout << v << '\n';
  }
}
