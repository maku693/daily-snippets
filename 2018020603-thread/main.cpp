#include <chrono>
#include <iostream>
#include <thread>
#include <type_traits>

template <
    class Rep,
    class Period,
    class Function,
    class... Args
>
std::result_of_t<Function(Args...)>
exec_in(
    const std::chrono::duration<Rep, Period>& min_interval,
    Function&& f, 
    Args&&... args
)
{
    const auto now = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_until(now + min_interval);
    f(args...);
}

void loop(int i = 0)
{
    std::cout
        << i
        << ' '
        << std::chrono::high_resolution_clock::now().time_since_epoch().count()
        << '\n';
    exec_in(std::chrono::seconds(1), loop, i + 1);
}

int main() {
    loop();
}

