struct foo{};

template <class T>
auto operator+(T n, foo f) {
    return n;
}

template <class A, class B>
auto add(A a, B b) {
    return a + b;
}

int main() {
    int x = 1;
    double y = 2.3;
    auto z = add(x, y);
    auto z_ = add(y, x);
    foo f{};
    auto z__ = add(x, f);
}
