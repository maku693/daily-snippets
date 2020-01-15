#include <iostream>
#include <string>
#include <vector>

enum class token_type {};

std::ostream &operator<<(std::ostream &os, const token_type &type) noexcept {
  const auto str = [&type] {
    switch (type) {
    default:
      return "Invalid token type";
    }
  }();
  return os;
}

struct token {
  token_type type;
  std::string str;
};

std::ostream &operator<<(std::ostream &os, const token &token) noexcept {
  return os << "token type: " << token.type << ", "
            << "string: " << token.str;
}

std::vector<token> parse(std::string &&str) noexcept {
  // TODO
  return {};
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "error: no program provided\n";
    return 1;
  }

  const auto parse_result = parse(argv[1]);

  std::cout << "parse result: " << std::endl;
  for (const auto &token : parse_result) {
    std::cout << token;
  }
  std::cout << std::endl;
}
