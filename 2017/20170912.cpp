#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v(10);
    std::iota(std::begin(v), std::end(v), 0);

    const auto it =
        std::partition(std::begin(v), std::end(v),
            [](const auto& i) { return i % 2 == 0; });

    auto os = std::ostream_iterator<int>(std::cout, ", ");
    std::copy(std::begin(v), it, os);
    std::cout << "\n";
    std::copy(it, std::end(v), os);
}
