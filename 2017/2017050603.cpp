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
auto makeStore(ReducerT&& reducer, StateT&& state = reducer())
{
    return Store<
        typename std::decay<ReducerT>::type,
        typename std::decay<StateT>::type
    >(std::forward<ReducerT>(reducer), std::forward<StateT>(state));
}

// --

namespace MyEvents {
    struct Increment final {};
}

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
    auto store1 = makeStore(MyReducer(), MyState());

    store1.subscribe(
        [&store1]()
        {
            std::cout << store1.getState().getCounter() << std::endl;
        }
    );

    auto store2 = makeStore(
        [](const int prevState, const MyEvents::Increment&)
        {
            return prevState + 1;
        },
        10
    );

    store2.subscribe(
        [&store2]()
        {
            std::cout << store2.getState() << std::endl;
        }
    );

    store1.dispatch(MyEvents::Increment());
    store2.dispatch(MyEvents::Increment());
}
