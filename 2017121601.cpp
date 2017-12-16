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

template <class F, class... Ts>
static constexpr void for_each_types(F&& f) { }

template <class F, class Car, class... Cdr>
static constexpr void for_each_types(F&& f)
{
    for_each_types<Cdr...>(f);
    f(std::forward<Car>());
}

template <std::size_t I, class... Ts>
struct visit_type {
    template <class F>
    static constexpr void at(const std::size_t i, F&& f)
    {
        if (i == I) {
            f(type_at_t<I, Ts...>{});
        } else {
            visit_type<I + 1, Ts...>::at(i, std::forward<F>(f));
        }
    }
};

template <class... Ts>
struct type_list {
    using size = std::integral_constant<std::size_t, sizeof...(Ts)>;

    template <std::size_t i>
    using at = type_at_t<i, Ts...>;

    template <class F>
    constexpr static void for_each(F&& f)
    {
        for_each_types<Ts...>(f);
    }

    template <class F>
    constexpr static void visit(const std::size_t i, F&& f)
    {
        visit_type<0, Ts...>::at(i, std::forward<F>(f));
    }
};

int main() { }
