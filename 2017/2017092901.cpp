#include<iostream>

template<class Drawable>
void draw(const Drawable& d) {
  d.draw();
}

struct MockDrawable {
  void draw() {
    std::cout << "I'm being drew!\n";
  }
}

int main() {
  MockDrawable d{};
  draw(d);
}
