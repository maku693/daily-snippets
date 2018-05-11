// This doesn't compile...
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

template <class ReducerT>
auto makeStore(ReducerT&& reducer)
{
    using R = typename std::decay<ReducerT>::type;
    using S = decltype(reducer());
    return Store<R, S>(
        std::forward<R>(reducer),
        reducer()
    );
}

template <class ReducerT, class StateT>
auto makeStore(ReducerT&& reducer, StateT&& state)
{
    using R = typename std::decay<ReducerT>::type;
    using S = typename std::decay<StateT>::type;
    return Store<R, S>(
        std::forward<R>(reducer),
        std::forward<S>(state)
    );
}

// --

namespace MyEvents {
    struct Increment final {};
}

int main()
{
    auto reducer =
        [](const int prevState, const auto event)
        {
            return prevState;
        };

    auto store1 = makeStore(reducer, 10);

    store1.subscribe(
        [&store1]()
        {
            std::cout << store1.getState() << std::endl;
        }
    );

    auto store2 = makeStore(reducer);

    store2.subscribe(
        [&store2]()
        {
            std::cout << store2.getState() << std::endl;
        }
    );

    store1.dispatch(MyEvents::Increment());
    store2.dispatch(MyEvents::Increment());
}
