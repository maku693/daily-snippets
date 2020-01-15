#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <type_traits>

template <
    class Rep,
    class Period,
    class Function,
    class... Args
>
decltype(auto) exec_in(
    const std::chrono::duration<Rep, Period>& min_interval,
    Function&& f,
    Args&&... args
)
{
    const auto now = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_until(now + min_interval);
    return std::invoke(std::forward<Function>(f), std::forward<Args>(args)...);
}

void loop(int i)
{
    using namespace std::chrono_literals;
    std::cout
        << i
        << ' '
        << std::chrono::high_resolution_clock::now().time_since_epoch().count()
        << '\n';
    exec_in(1s, loop, i + 1);
}

int main() {
    using namespace std::chrono_literals;
    std::thread(loop, 0).detach();
    std::this_thread::sleep_until(std::chrono::system_clock::time_point::max());
}
