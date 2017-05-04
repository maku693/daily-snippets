#include <array>
#include <chrono>
#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

template <class StateT, class EventT>
constexpr StateT Reducer(const StateT&, const EventT&);

template <class StateT>
struct StoreWithValueState final {
private:
    using ListenerT = std::function<void()>;

    StateT m_state;
    std::vector<ListenerT> m_listeners;

public:
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

template <class StateT>
struct StoreWithStatePoniter final {
private:
    using ListenerT = std::function<void()>;

    std::unique_ptr<StateT> m_state;
    std::vector<ListenerT> m_listeners;

public:
    StoreWithStatePoniter() : m_state(std::make_unique<StateT>()) {}

    StoreWithStatePoniter(std::unique_ptr<StateT>&& state) : m_state(std::move<state>) {}

    constexpr StateT getState() const
    {
        return this->m_state;
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
    std::array<int, 10000> foobar;

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
    std::chrono::high_resolution_clock::rep last;

    StoreWithValueState<MyState> sv;
    sv.subscribe(
        [&sv, &last]()
        {
            std::cout <<
                "Value   : " <<
                std::chrono::high_resolution_clock::now().
                    time_since_epoch().count() - last <<
                std::endl;
        }
    );

    StoreWithStatePoniter<MyState> sp;
    sp.subscribe(
        [&sv, &last]()
        {
            std::cout <<
                "Pointer : " <<
                std::chrono::high_resolution_clock::now().
                    time_since_epoch().count() - last <<
                std::endl;
        }
    );

    last = std::chrono::high_resolution_clock::now().
        time_since_epoch().count();
    sv.dispatch(MyEvents::Increment());

    last = std::chrono::high_resolution_clock::now().
        time_since_epoch().count();
    sp.dispatch(MyEvents::Increment());
}

