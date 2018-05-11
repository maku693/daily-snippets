#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template <class StateT, class EventT>
constexpr StateT Reducer(const StateT&, const EventT&);

template <class StateT>
struct Store final {
private:
    using ListenerT = std::function<void()>;

    std::unique_ptr<StateT> m_state;
    std::vector<ListenerT> m_listeners;

public:
    Store() : m_state(std::make_unique<StateT>()) { }

    Store(const StateT& state)
        : m_state(std::make_unique<StateT>(state)) { }

    Store(StateT&& state)
        : m_state(std::make_unique<StateT>(state)) { }

    constexpr StateT getState() const
    {
        return *this->m_state;
    }

    template <class EventT>
    void dispatch(const EventT& event)
    {
        this->m_state = std::make_unique<StateT>(
            Reducer(*this->m_state, event)
        );

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
    struct Decrement final {};
}

template<>
constexpr MyState Reducer(
    const MyState& prevState,
    const MyEvents::Increment&
)
{
    auto state = MyState(prevState);
    state.setCounter(prevState.getCounter() + 1);
    return state;
}

template<>
constexpr MyState Reducer(
    const MyState& prevState,
    const MyEvents::Decrement&
)
{
    auto state = MyState(prevState);
    state.setCounter(prevState.getCounter() - 1);
    return state;
}

int main()
{
    MyState initialState1;
    initialState1.setCounter(10);

    Store<MyState> store1(initialState1);

    store1.subscribe(
        [&store1]()
        {
            std::cout << store1.getState().getCounter() << std::endl;
        }
    );

    store1.dispatch(MyEvents::Increment());


    MyState initialState2;
    initialState2.setCounter(20);

    Store<MyState> store2(std::move(initialState2));

    store2.subscribe(
        [&store2]()
        {
            std::cout << store2.getState().getCounter() << std::endl;
        }
    );

    store2.dispatch(MyEvents::Decrement());
}

