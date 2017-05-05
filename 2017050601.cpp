#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template <class StateT, class ReducerT>
struct Store final {
private:
    using ListenerT = std::function<void()>;

    StateT m_state;
    ReducerT m_reducer;

    std::vector<ListenerT> m_listeners;

public:
    Store() = default;

    Store(StateT&& state) noexcept
        : m_state(std::move(state)) { }

    constexpr auto getState() const noexcept
    {
        return this->m_state;
    }

    template <class EventT>
    void dispatch(const EventT& event)
    {
        this->m_state = std::move(m_reducer(this->m_state, event));

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

struct MyReducer {
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
    Store<MyState, MyReducer> store;

    store.subscribe(
        [&store]()
        {
            std::cout << store.getState().getCounter() << std::endl;
        }
    );

    store.dispatch(MyEvents::Increment());
}

