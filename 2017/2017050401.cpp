#include <functional>
#include <iostream>
#include <vector>

template <class StateT, class EventT>
constexpr StateT Reducer(const StateT&, const EventT&);

template <class StateT>
struct Store final {
private:
    using ListenerT = std::function<void()>;

    StateT m_state;
    std::vector<ListenerT> m_listeners;

public:
    Store() = default;

    Store(StateT state) : m_state(state) {};

    constexpr StateT getState() const
    {
        return this->m_state;
    }

    template <class EventT>
    void dispatch(const EventT& event)
    {
        this->m_state = Reducer(this->m_state, event);

        for (auto listener : this->m_listeners) {
            listener();
        }
    }

    void subscribe(ListenerT listener) noexcept
    {
        m_listeners.push_back(listener);
    }
};

struct MyState final {
private:
    int counter = 0;
public:
    constexpr int getCounter() const noexcept
    {
        return this->counter;
    }

    constexpr void setCounter(int value) noexcept
    {
        this->counter = value;
    }
};

namespace MyEvents {
    struct Increment final {};
    struct Decrement final {};
}

template<>
constexpr MyState Reducer(const MyState& prevState, const MyEvents::Increment&)
{
    auto state = MyState(prevState);
    state.setCounter(prevState.getCounter() + 1);
    return state;
}

template<>
constexpr MyState Reducer(const MyState& prevState, const MyEvents::Decrement&)
{
    auto state = MyState(prevState);
    state.setCounter(prevState.getCounter() - 1);
    return state;
}

int main()
{
    Store<MyState> store;
    store.subscribe([&store]() {
        std::cout << store.getState().getCounter() << std::endl;
    });

    store.dispatch(MyEvents::Increment());
    store.dispatch(MyEvents::Increment());
    store.dispatch(MyEvents::Decrement());
    store.dispatch(MyEvents::Increment());
}

