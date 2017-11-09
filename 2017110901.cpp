#include <future>
#include <thread>

int main() {
  std::future<int> f = std::async(std::launch::async, []{ return 100; });
  f.wait();
  std::cout << f.get(); << '\n';
}

