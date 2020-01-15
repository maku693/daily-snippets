#include <iostream>
#include <chrono>

template <class T>
void put_delta(const T& delta) {
    std::cout
        << "delta: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(delta).count()
        << " msec\n";
}


int main() {
    auto last_time = std::chrono::high_resolution_clock::now();
    while(std::cin.get()) {
        const auto now = std::chrono::high_resolution_clock::now();
        put_delta(now - last_time);
        last_time = now;
    }
}

