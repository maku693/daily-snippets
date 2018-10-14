#include <variant>
#include <string>
#include <string_view>
#include <iostream>

struct visitor {
    void operator()(int x) {
        std::cout << "int: " << x << '\n';
    }

    void operator()(std::string_view x) {
        std::cout << "string_view: " << x << '\n';
    }
};

int main() {
    std::variant<int, std::string> v;
    v = 42;
    std::visit(visitor{}, v);
    v = "foobar";
    std::visit(visitor{}, v);
}
