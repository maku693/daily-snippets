#include <utility>

template <class T> struct num_wrapper {
  T value;

  template <class T>
  constexpr auto operator*=(const num_wrapper<T> &rhs) noexcept {
    this->value *= rhs.value;
    return *this;
  }

  template <class T>
  constexpr auto operator*(const num_wrapper<T> &rhs) const noexcept {
    num_wrapper<int> t{*this};
    return std::move(t) *= rhs;
  }
};

template <class T> num_wrapper(T &&)->num_wrapper<T>;

int main() {
  constexpr num_wrapper<int> a{1};
  constexpr num_wrapper<int> b{2};
  auto c = num_wrapper{1} *= a;
  constexpr auto actual = a * b;
}
