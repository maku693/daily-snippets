#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main()
{
    unsigned short numberOfAvailableThreads = std::thread::hardware_concurrency();

    std::vector<std::thread> workers;

    for (int i = 0; i < numberOfAvailableThreads; i++) {
        workers.push_back(
            std::thread([i](){
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << i;
            })
        );
    }

    std::cout << "Available threads: " << numberOfAvailableThreads << std::endl;
    for (auto& worker : workers) {
        worker.join();
    }
}
