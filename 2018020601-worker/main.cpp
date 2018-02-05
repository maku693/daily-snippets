#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

template <
    class Duration,
    class Function,
    class... Args
>
std::thread make_loop(
    Duration&& d,
    Function&& f, 
    Args&&... args
)
{
    return std::thread([&] {
        while (true) {
            f(args...);
            std::this_thread::sleep_for(Duration(d));
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

