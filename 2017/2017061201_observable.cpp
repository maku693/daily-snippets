
template <class Observer>
class ObserverTraits {
public:
    using ValueType = Observer::ValueType;
};

template <class Observable>
class ObservableTraits {
public:
    using ValueType = Observable::ValueType;
};

template <class T>
class ObserverFacade {
public:
    using ValueType = T;
    void onNext(ObserverTraits<ObserverFacade<T>>::ValueType) { };
    void onError(const std::exception& e) { throw e; };
    void onCompleted() { };
};

template <class T>
class ObservableFacade {
public:
    using ValueType = T;
    template <class Observer>
    void subscribe(Observer) { };
};

class MyObserver {
    void onNext(int value)
    {
        return value;
    }
};

class MyObservable : public ObservableFacade<int> {
    template <class Observer>
    void subscribe(const Observer& observer)
    {
        observer.onNext(1);
    }
};

