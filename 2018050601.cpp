#include <iostream>
#include <string>
#include <vector>

enum class token_type {};

struct token {
  token_type type;
  std::string str;
};

enum class parse_status {
  success,
  fail,
};

struct parse_result {
  parse_status status;
  std::vector<token> tokens;

  constexpr operator bool() const { return status == parse_status::success; }

  static const parse_result failed() {
    return parse_result{parse_status::fail, {}};
  }
};

parse_result parse(std::string &&str) {
  // TODO
  return parse_result::failed();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "error: no program provided\n";
    return 1;
  }

  const auto parse_result = parse(argv[1]);
  if (!parse_result) {
    std::cerr << "error: parse failed\n";
    return 1;
  }
}
