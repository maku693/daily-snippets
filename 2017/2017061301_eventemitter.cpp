#include <functional>
#include <vector>

template <class T>
class EventTraits {
public:
    using ValueType = T;
};

template <class T>
class EventEmitter {
public:
    using ValueType = typename EventTraits<T>::ValueType;
    using ListenerType = typename std::function<void(ValueType)>;

    EventEmitter() = default;

    void emit(ValueType value) {
        for (ListenerType listener : this->m_listeners)
        {
            listener(value);
        }
    }

    void listen(ListenerType listener)
    {
        this->m_listeners.push_back(listener);
    }

private:
    std::vector<ListenerType> m_listeners;
};

int main()
{
    EventEmitter<int> emitter;

    emitter.listen([](int i) { std::cout << i << std::endl; });

    emitter.emit(1);
    emitter.emit(2);
    emitter.emit(3);
    emitter.emit(4);

    return 0;
}
