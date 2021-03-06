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
        this->m_state =
            std::move_if_noexcept(m_reducer(this->m_state, event));

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
    return Store<
        typename std::decay<ReducerT>::type,
        typename std::decay<StateT>::type
    >(std::forward<ReducerT>(reducer), std::forward<StateT>(state));
}

// --

struct MyState final {
private:
    int m_counter = 0;

public:
    constexpr int getCounter() const noexcept
    {
        return this->m_counter;
    }

    constexpr void setCounter(int value) noexcept
    {
        this->m_counter = value;
    }
};

namespace MyEvents {
    struct Increment final {};
}

struct MyReducer final {
    constexpr MyState operator() (
        const MyState& prevState,
        const MyEvents::Increment&
    )
    {
        MyState state = prevState;
        state.setCounter(prevState.getCounter() + 1);
        return state;
    }
};

int main()
{
    auto store = makeStore(MyReducer(), MyState());

    store.subscribe(
        [&store]()
        {
            std::cout << store.getState().getCounter() << std::endl;
        }
    );

    store.dispatch(MyEvents::Increment());
}
