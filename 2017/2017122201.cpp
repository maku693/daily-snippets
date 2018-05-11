#include <array>
#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

template <std::size_t I, class... Ts>
struct type_at;

template <class Car, class... Cdr>
struct type_at<0, Car, Cdr...> {
    using type = Car;
};

template <std::size_t I, class... Ts>
struct type_at {
    using type = typename type_at<I - 1, Ts...>::type;
};

template <std::size_t I, class... Ts>
using type_at_t = typename type_at<I, Ts...>::type;

template <class... Ts>
struct for_each_types;

template <class Car, class... Cdr>
struct for_each_types<Car, Cdr...> {
    template <class F>
    static inline auto call(F&& f)
    {
        f(Car{});
        return for_each_types<Cdr...>::call(std::move(f));
    }
};

template <>
struct for_each_types<> {
    template <class F>
    static inline auto call(F&& f) { return std::move(f); }
};

template <class... Ts>
struct visit_type;

template <class Car, class... Cdr>
struct visit_type<Car, Cdr...> {
    template <class F>
    static inline auto at(const std::size_t i, F&& f)
    {
        if (i == 0) {
            f(Car{});
        }

        return visit_type<Cdr...>::at(i - 1, std::move(f));
    }
};

template <>
struct visit_type<> {
    template <class F>
    static inline auto at(const std::size_t i, F&& f) { return std::move(f); }
};

template <class... Ts>
struct type_list {
    using type = type_list<Ts...>;
    using size = std::integral_constant<std::size_t, sizeof...(Ts)>;

    template <std::size_t I>
    using at = type_at_t<I, Ts...>;

    template <class F>
    static auto for_each(F&& f)
    {
        return for_each_types<Ts...>::call(std::forward<F>(f));
    }

    template <class F>
    static auto visit(const std::size_t i, F&& f)
    {
        return visit_type<Ts...>::at(i, std::forward<F>(f));
    }
};

template <class T, T... Values>
struct integral_constant_list : public type_list<std::integral_constant<T, Values>...> {
    static auto to_array()
    {
        return std::array<T, sizeof...(Values)>{Values...};
    }

    static auto to_vector()
    {
        return std::vector<T>{Values...};
    }
};

template <class T, T... Values>
using single_type_list : public type_list<T, T{VALUES}...>;

template <char... Chars>
struct char_constant_list : public integral_constant_list<char, Chars...>
{
    static auto to_string()
    {
        return std::string{Chars...};
    }
};

#include <iostream>

int main()
{
    using one_to_four = integral_constant_list<int, 1, 2, 3, 4>;
    std::cout << one_to_four::size{} << "\n";
    one_to_four::visit(0, [](auto tag) { std::cout << tag << "\n"; });
    one_to_four::for_each([](auto tag) { std::cout << tag; });
    std::cout << "\n";

    using hello = char_constant_list<'h', 'e', 'l', 'l', 'o'>;
    std::cout << hello::size{} << "\n";
    hello::visit(1, [](auto tag) { std::cout << tag << "\n"; });
    hello::for_each([](auto tag) { std::cout << tag; });
    std::cout << "\n";
    std::cout << hello::to_string() << "\n";
}
