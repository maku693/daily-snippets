#include <iostream>
#include <string>
#include <vector>

enum class token_type {};

struct token {
  token_type type;
  std::string str;
};

struct parse_result_t {
  bool status;
  std::vector<token> tokens;

  constexpr operator bool() const { return status; }
};

parse_result_t parse(std::string &&str) { return parse_result_t{false, {}}; }

int main(int argc, char *argv[]) {
  if (argc == 0)
    return;

  const char *prog = argv[0];

  const auto parse_result = parse(prog);
  if (!parse_result) {
    return -1;
  }
}
