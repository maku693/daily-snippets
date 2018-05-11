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
    using R = typename std::decay<ReducerT>::type;
    using S = typename std::decay<StateT>::type;
    return Store<R, S>{
        std::forward<ReducerT>(reducer),
        std::forward<StateT>(state)
    };
}

// --

namespace MyEvents {
    struct Increment final {};
}

struct MyReducer final {

    auto operator()(const int prevState, const MyEvents::Increment&)
    {
        return prevState + 1;
    }

};

int main()
{
    auto store = makeStore(MyReducer(), 0);

    store.subscribe(
        [&store]()
        {
            std::cout << store.getState() << std::endl;
        }
    );

    store.dispatch(MyEvents::Increment());
}
