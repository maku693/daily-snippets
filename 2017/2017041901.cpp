#include <iostream>

template <class T>
struct some_traits {
    static constexpr bool isMixedIn() { return false; }
};

struct some_mixin {
    static constexpr bool isMixedIn() { return true; }
};

template <>
struct some_traits<int> : some_mixin {};

template <class T>
constexpr bool isTraitMixedIn()
{
    return some_traits<T>::isMixedIn();
}

int main()
{
    std::cout << isTraitMixedIn<int>() << std::endl;
    std::cout << isTraitMixedIn<float>() << std::endl;
    return 0;
}
