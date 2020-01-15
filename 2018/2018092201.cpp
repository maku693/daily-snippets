#include <stdexcept>
#include <functional>

void fail() { throw std::runtime_error("test failed"); }

int test_foobar() {
    fail();
    return 0;
}

int main() {
    std::function<int()> tests[] {test_foobar};
    for (const auto& test : tests) {
        if (int result = test(); result != 0) {
            return result;
        }
    }
}
