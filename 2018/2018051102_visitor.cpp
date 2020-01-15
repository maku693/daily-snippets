#include <iostream>
#include <string>
#include <variant>
#include <vector>

template <class... Ts> struct overloaded_functor : Ts... {
  using Ts::operator()...;
};

template <class... Ts>
overloaded_functor<Ts...> make_overloaded(Ts... functors) {
  return {functors...};
}

int main() {
  using namespace std::string_literals;

  using var_t = std::variant<int, std::string>;

  std::vector<var_t> vec{1, "variant"s};
  for (const auto &var : vec) {
    std::visit(make_overloaded(
                   [](int arg) { std::cout << "int: " << arg << std::endl; },
                   [](const std::string &arg) {
                     std::cout << "string: " << arg << std::endl;
                   }),
               var);
  }
}
