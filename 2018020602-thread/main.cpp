#include <chrono>
#include <iostream>
#include <thread>

template <
    class Rep,
    class Period,
    class Function,
    class... Args
>
std::thread make_loop(
    const std::chrono::duration<Rep, Period>& min_interval,
    const Function& f, 
    const Args&... args
)
{
    return std::thread([&] {
        while (true) {
            const auto now = std::chrono::high_resolution_clock::now();
            f(args...);
            std::this_thread::sleep_until(now + min_interval);
        }
    });
}

int main() {
    auto loop = make_loop(std::chrono::seconds(1), [] {
        std::cout
            << std::chrono::steady_clock::now()
                .time_since_epoch()
                .count()
            << '\n';

    });
    loop.join();
}

