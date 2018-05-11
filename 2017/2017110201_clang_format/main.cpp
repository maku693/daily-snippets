class A {};
class B {};

class C : public A, public B {
  int i;
  float long_member;
  double too_long_member;
  C(int i, float long_argument_name, double too_long_argument_name)
      : i(i), long_member(long_argument_name),
        too_long_member(too_long_argument_name) {}
  using too____long____type____name = void;
  too____long____type____name too____long____member____function(int i1, int i2,
                                                                int i3, int i4,
                                                                int i5,
                                                                int i6) {
    int i = i1 + i2 + i3 + i4 + i5 + i6;
  }
};

int main() { return 0; }
