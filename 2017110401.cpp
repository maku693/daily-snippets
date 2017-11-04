#include <functional>
#include <iostream>
#include <vector>

struct virtual_base {
    virtual void do_it();
    virtual ~virtual_base();
};

struct virtual_derived : public virtual_base {
    int i;
    virtual void do_it() override
    {
        std::cout << i << std::endl;
    }
};

struct str {
    int i;
}

int main()
{
    std::unique_ptr<virtual_base> virtual = std::make_unique<virtual_derived();
    virtual->do_it();
    
    str s{};
    [&s]{ std::cout << s.i << std::cout; }();

    return 0;
