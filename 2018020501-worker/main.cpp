#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

void f() {
    while (true) { 
        const auto now = std::chrono::high_resolution_clock::now();
        std::cout << now.time_since_epoch().count();
        std::this_thread::sleep_for(std::chrono::microseconds(16667));
    }
}

int main() {
    std::thread t(f);
    t.detach();
}

