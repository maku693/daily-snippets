struct base {
    static constexpr bool example(bool v) { return v; }
};

struct derived : public base {};

int main()
{
    if (derived::example(true)) {
        return 0;
    } else {
        return -1;
    }
}
