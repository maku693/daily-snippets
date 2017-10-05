#include <iostream>

template <class T>
struct ActorTraits {
  using ActorType = T;
  static void awake(const ActorType& a) { a.awake(); }
};

struct DumbActor {
  void awake() { std::cout << "Hello, world!\n"; }
}

int main() {
  DumbActor d{};
  ActorTraits::awake(d);
}
