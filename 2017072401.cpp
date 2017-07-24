#include <algorithm>
#include <vector>
#include <iostream>

int main() {
     std::vector<int> v { 1, 2, 3 };
     const auto index = std::distance(v.cbegin(), std::find(v.cbegin(), v.cend(), 2));
     std::cout << index << std::endl;
}
