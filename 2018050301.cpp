#include <future>

template <class Function, class... Args>
auto then(Function &&)
{
    return
}

int main() {
    std::async([]{ return 123; });
}
