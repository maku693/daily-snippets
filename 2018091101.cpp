#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

int main() {
  std::map<std::string, int> m;
  m["z"] = 1;
  m["y"] = 2;
  m["x"] = 3;
  for (const auto [k, v] : m) {
      std::cout << k << ': ' << v << '\n';
  }

  std::unordered_map<std::string, int> um;
  um["z"] = 1;
  um["y"] = 2;
  um["x"] = 3;
  for (const auto [k, v] : um) {
      std::cout << k << ': ' << v << '\n';
  }
}
