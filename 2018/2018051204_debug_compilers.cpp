#include <utility>

template <class T> struct num_wrapper {
  T value;

  template <class U>
  constexpr auto operator*=(const num_wrapper<U> &rhs) noexcept {
    this->value *= rhs.value;
    return *this;
  }
};

template <class T> num_wrapper(T &&)->num_wrapper<T>;

template <class T, class U>
constexpr auto operator*(const num_wrapper<T> &lhs,
                         const num_wrapper<U> &rhs) const noexcept {
  return num_wrapper<T>{lhs} *= rhs;
}

int main() {
  constexpr num_wrapper<int> a{1};
  constexpr num_wrapper<int> b{2};
  constexpr auto c = a * b;
  constexpr auto d = num_wrapper<int>{3} * num_wrapper<int>{4};
  constexpr auto e = d *= num_wrapper<int>{5};
  constexpr auto f = num_wrapper<int>{6} *= e;
}
