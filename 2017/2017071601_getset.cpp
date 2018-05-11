struct getset1 {
    int m_value;

    constexpr int value() const
    {
        return m_value;
    }

    constexpr void value(int new_value)
    {
        m_value = new_value;
    }
};

template <class T>
struct property_traits {
    using value_type = T;
    using set_arg_type = T;
};

template <class T>
struct property {
public:
    std::function<property_traits<T>::value_type(void)> get;
    std::function<void(property_traits<T>::set_arg_type)> set;
    setter_traits<T>::value_type value;
};

auto make_property(std::function<property_traits<T>::value_type(void)>,
    std::function<void(property_traits<T>::set_arg_type)>)
{
    return
}

struct setter_user {
    property<int> value;
};

int main()
{
    getset1 gs1;
    gs1.value(1);
    gs1.value();
}
