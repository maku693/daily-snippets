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
struct type_at {
    using type = typename type_at<i - 1, Ts...>::type;
};

template <std::size_t i, class... Ts>
using type_at_t = typename type_at<i, Ts...>::type;

template <class... Ts>
struct for_each_types;

template <class Car, class... Cdr>
struct for_each_types<Car, Cdr...> {
    template <class F>
    static auto call(F&& f)
    {
        f(Car{});
        return for_each_types<Cdr...>::call(std::move(f));
    }
};

template <class... Ts>
struct for_each_types {
    template <class F>
    static auto call(F&& f) { return f; }
};

template <std::size_t I, class... Ts>
struct visit_type {
    template <class F>
    static constexpr auto at(const std::size_t i, F&& f)
    {
        if (i == I) {
            f(type_at_t<I, Ts...>{});
            return std::move(f);
        }

        return visit_type<I + 1, Ts...>::at(i, std::forward<F>(f));
    }
};

template <class... Ts>
struct type_list {
    using size = std::integral_constant<std::size_t, sizeof...(Ts)>;

    template <std::size_t i>
    using at = type_at_t<i, Ts...>;

    template <class F>
    static auto for_each(F&& f)
    {
        return for_each_types<Ts...>::call(f);
    }

    template <class F>
    static auto visit(const std::size_t i, F&& f)
    {
        return visit_type<0, Ts...>::at(i, std::forward<F>(f));
    }
};

int main() { }
