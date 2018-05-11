#include <iostream>
#include <string>
#include <variant>
#include <vector>

template <class... Ts> struct overloaded_functor : Ts... {
  using Ts::operator()...;
};

template <class... Ts> overloaded_functor(Ts...)->overloaded_functor<Ts...>;

int main() {
  using var_t = std::variant<int, std::string>;

  std::vector<var_t> vec{1, "variant"};

  const auto visitor = overloaded_functor{
      [](int arg) { std::cout << "int: " << arg << std::endl; },
      [](const std::string &arg) {
        std::cout << "string: " << arg << std::endl;
      }};

  for (const auto &variant : vec) {
    std::visit(visitor, variant);
  }
}
