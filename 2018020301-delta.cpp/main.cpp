#include <iostream>
#include <chrono>

template <class T>
void put_delta(const T& delta) {
    std::cout << delta << '\n';
}


int main() {
    auto last_time = std::chrono::microseconds::zero();
    while(std::cin) {
        const auto now = std::chrono::high_resolution_clock::now();
        put_delta(now - last_time);
        last_time = now;
    }
}

