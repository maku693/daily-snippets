#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template <class StateT, class EventT>
StateT Reducer(const StateT, const EventT&);

template <class StateT>
struct Store final {
private:
    using ListenerT = std::function<void()>;

    StateT m_state;
    std::vector<ListenerT> m_listeners;

public:
    Store() = default;

    Store(StateT&& state) noexcept
        : m_state(std::move(state)) { }

    constexpr StateT getState() const noexcept
    {
        return this->m_state;
    }

    template <class EventT>
    void dispatch(const EventT& event)
    {
        this->m_state = std::move(Reducer(this->m_state, event));

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
}

using MyStateRef = std::shared_ptr<MyState>;

template<>
MyStateRef Reducer(
    const MyStateRef prevState,
    const MyEvents::Increment&
)
{
    MyState state = *prevState;
    state.setCounter(prevState->getCounter() + 1);
    return std::make_shared<MyState>(state);
}

template<>
int Reducer(
    const int prevState,
    const MyEvents::Increment&
)
{
    return 1 + prevState;
}

int main()
{
    Store<MyStateRef> storeOfPtr(std::make_shared<MyState>());
    Store<int> storeOfValue(0);

    storeOfPtr.subscribe(
        [&storeOfPtr]()
        {
            std::cout << storeOfPtr.getState()->getCounter() << std::endl;
        }
    );
    storeOfValue.subscribe(
        [&storeOfValue]()
        {
            std::cout << storeOfValue.getState() << std::endl;
        }
    );

    storeOfPtr.dispatch(MyEvents::Increment());
    storeOfValue.dispatch(MyEvents::Increment());
}

