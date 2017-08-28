template <class T>
auto create_maybe(T);

struct Nothing {};

template <class T>
struct Just {
    T val;
};

template<class T>
auto create_maybe(T arg)
{
    return Just<T>{arg};
}

template <>
auto create_maybe(Nothing nop)
{
    return nop;
}

int main()
{
    create_maybe(1);
}
