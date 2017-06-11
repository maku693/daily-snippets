#include <iostream>

template <class T>
class base {
    constexpr int getValue() const { return 0; };

    void printValue()
    {
        std::cout << static_cast<T&>(*this).getValue() << std::endl;
    }
};

class derived : base<derived> {
    constexpr int getValue() const { return 42; };
};

int main()
{
    base b;
    derived d;

    b.printValue();
    d.printValue();

    return 0;
}
