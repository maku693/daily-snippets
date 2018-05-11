#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template <class ReducerT, class StateT>
struct Store final {
private:
    using ListenerT = std::function<void()>;

    ReducerT m_reducer;
    StateT m_state;

    std::vector<ListenerT> m_listeners;

public:
    Store() = default;

    Store(ReducerT&& reducer, StateT&& state) noexcept
        : m_reducer(std::move_if_noexcept(reducer))
        , m_state(std::move_if_noexcept(state))
    { }

    constexpr auto getState() const noexcept
    {
        return this->m_state;
    }

    template <class EventT>
    void dispatch(const EventT& event)
    {
        this->m_state = m_reducer(this->m_state, event);

        for (auto listener : this->m_listeners) {
            listener();
        }
    }

    void subscribe(ListenerT listener) noexcept
    {
        m_listeners.push_back(listener);
    }
};

template <class ReducerT, class StateT>
auto makeStore(ReducerT&& reducer, StateT&& state)
{
    return Store<ReducerT, StateT> {
        std::forward<ReducerT>(reducer),
        std::forward<StateT>(state)
    };
}

// --

// From https://ngathanasiou.wordpress.com/2015/10/20/lambda-hackery-overloading-sfinae-and-copyrights/
template <class... F>
struct overload_set : F...
{
    overload_set(F... f) : F(f)... {}
};

template <class... F>
auto overload(F... f)
{
    return overload_set<F...>(f...);
}

// --

namespace MyEvents {
    struct Increment final {};
}

int main()
{
    auto reducer = overload(
        [](const int prevState, const MyEvents::Increment&)
        {
            return prevState + 1;
        }
    );

    auto store = makeStore(reducer, 0);

    store.subscribe(
        [&store]()
        {
            std::cout << store.getState() << std::endl;
        }
    );

    store.dispatch(MyEvents::Increment());
}
