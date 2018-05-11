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

struct func {
    int i;
    std::function<void()> get_doer()
    {
        return [this] {
            std::cout << this->i << std::endl;
        };
    }
}

int main()
{
    std::vector<virtual_base> virtuals{};
    std::vector<func> funcs{};

    return 0;
}
