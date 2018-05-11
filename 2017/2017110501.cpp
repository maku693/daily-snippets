#include <functional>
#include <iostream>
#include <vector>
#include <memory>

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
};

int main()
{
    std::unique_ptr<virtual_base> v = std::make_unique<virtual_derived>();
    v->do_it();

    str s{};
    std::function<void()> f = [&s]{ std::cout << s.i << std::endl; };
    f();

    return 0;
}
