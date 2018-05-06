#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

enum class token_type {
  paren_open,
  paren_close,
  literal_number,
  symbol,
};

std::ostream &operator<<(std::ostream &os, const token_type &type) noexcept {
  switch (type) {
  case token_type::paren_open:
    os << "paren_open";
    break;
  case token_type::paren_close:
    os << "paren_close";
    break;
  case token_type::literal_number:
    os << "literal_number";
    break;
  case token_type::symbol:
    os << "symbol";
    break;
  default:
    break;
  }
  return os;
}

struct token {
  token_type type;
  std::string str;
};

std::ostream &operator<<(std::ostream &os, const token &token) noexcept {
  return os << "type: " << token.type << ",\t" << "str: " << token.str;
}

class tokenizer {
public:
  tokenizer() = delete;
  explicit tokenizer(std::string &&src) noexcept;
  std::vector<token> tokenize() noexcept;

private:
  const std::string src;

  std::string::const_iterator head;
  std::string buf;

  std::vector<token> tokens;

  bool is_whitespace() noexcept;
  bool is_paren_open() noexcept;
  bool is_paren_close() noexcept;
  bool is_literal_number() noexcept;
  bool is_symbol() noexcept;

  void whitespace() noexcept;
  void paren_open() noexcept;
  void paren_close() noexcept;
  void literal_number() noexcept;
  void symbol() noexcept;

  char peek() noexcept;
  void consume() noexcept;
  void flush() noexcept;
};

tokenizer::tokenizer(std::string &&src) noexcept
    : src(src), head(this->src.cbegin()) {}

std::vector<token> tokenizer::tokenize() noexcept {
  while (head < src.cend()) {
    whitespace();
    paren_open();
    paren_close();
    literal_number();
    symbol();
  }
  return tokens;
}

bool tokenizer::is_whitespace() noexcept {
  std::array<char, 10> candidates{' ', '\f', '\n', '\r', '\t', '\v'};
  const auto result = std::find(candidates.cbegin(), candidates.cend(), peek());
  return result != candidates.cend();
}

bool tokenizer::is_paren_open() noexcept { return peek() == '('; }

bool tokenizer::is_paren_close() noexcept { return peek() == ')'; }

bool tokenizer::is_literal_number() noexcept {
  std::array<char, 10> candidates{'0', '1', '2', '3', '4',
                                  '5', '6', '7', '8', '9'};
  const auto result = std::find(candidates.cbegin(), candidates.cend(), peek());
  return result != candidates.cend();
}

bool tokenizer::is_symbol() noexcept {
  std::array<char, 26> candidates{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                  'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                  's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  const auto result = std::find(candidates.cbegin(), candidates.cend(), peek());
  return result != candidates.cend();
}

void tokenizer::whitespace() noexcept {
  while (is_whitespace()) {
    consume();
  }
  flush();
}

void tokenizer::paren_open() noexcept {
  if (is_paren_open()) {
    consume();
    tokens.emplace_back(token{token_type::paren_open, buf});
  }
  flush();
}

void tokenizer::paren_close() noexcept {
  if (is_paren_close()) {
    consume();
    tokens.emplace_back(token{token_type::paren_close, buf});
  }
  flush();
}

void tokenizer::literal_number() noexcept {
  while (is_literal_number()) {
    consume();
  }
  if (!buf.empty()) {
    tokens.emplace_back(token{token_type::literal_number, buf});
  }
  flush();
}

void tokenizer::symbol() noexcept {
  while (is_symbol()) {
    consume();
  }
  if (!buf.empty()) {
    tokens.emplace_back(token{token_type::symbol, buf});
  }
  flush();
}

char tokenizer::peek() noexcept { return *head; }

void tokenizer::consume() noexcept {
  buf.push_back(peek());
  head++;
}

void tokenizer::flush() noexcept { buf.clear(); }

std::vector<token> tokenize(std::string &&str) noexcept {
  tokenizer tokenizer(std::forward<std::string>(str));
  return tokenizer.tokenize();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "error: no program provided\n";
    return 1;
  }

  const auto tokenize_result = tokenize(argv[1]);

  std::cerr << "tokens: " << std::endl;
  for (const auto &token : tokenize_result) {
    std::cerr << token << std::endl;
  }
}
