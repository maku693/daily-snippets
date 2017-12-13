#include <cstddef>
#include <functional>
#include <type_traits>

template <class... Ts>
struct type_list {
    using type = enumeration<Ts...>;
    using size = std::integral_constant<std::size_t, sizeof...(Ts)>;

private:
    template <std::size_t i, class... Ts>
    struct item_at;

    template <class Car, class... Cdr>
    struct item_at<0, Car, Cdr...> {
        using type = Car;
    };

    template <std::size_t i, class... List>
    struct item_at<T, i, List...> {
        using type = item_at<i - 1, Ts...>::type;
    };

public:
    template <std::size_t i>
    using at = item_at<i, Ts...>::type;

};



