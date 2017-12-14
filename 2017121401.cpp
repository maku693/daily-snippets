#include <cstddef>
#include <functional>
#include <type_traits>

template <std::size_t i, class... Ts>
struct type_at;

template <class Car, class... Cdr>
struct type_at<0, Car, Cdr...> {
    using type = Car;
};

template <std::size_t i, class... Ts>
struct type_at<i, Ts...> {
    using type = item_at<i - 1, Ts...>::type;
};

template <class... Ts>
struct for_each_types;

template <class T>
struct for_each_types<T> {
    template <class Fn>
    static void operator()(Fn&& f) const { }
};

template <class Car, class... Cdr>
struct for_each_types<Car, Cdr...> {
    template <class Fn>
    static void operator()(Fn&& f) const
    {
        for_each_items::<Cdr...>::do_next(f);
        f(Car);
    }
};

template <class... Ts>
struct type_list {
    using type = type_list<Ts...>;
    using size = std::integral_constant<std::size_t, sizeof...(Ts)>;

    template <std::size_t i>
    using at = type_at<i, Ts...>::type;

    template <class Fn>
    constexpr static for_each(Fn&& f) const
    {
        for_each_types<Ts...>(f);
    }

    template <class Fn>
    constexpr static visit(std::size_t i, Fn&& f) const
    {
        f(at<i>);
    }
};

