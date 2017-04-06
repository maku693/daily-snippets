template <
    class SourceT,
    class Traits = ObservableTraits<SourceT>
> struct Observable;

template <
    class SourceT,
    class Traits = ObserverTraits<SourceT>
> struct Observer;

template <typename T>
struct ObservableTraits {
  static void subscribe(const Observer<T>&) { /* Nope */ }
};

template <typename T>
struct Observable {
  void onNext(const Observer<T> observer) {
    ObservableTraits<T>::subscribe(observer);
  }
};

template <typename T>
struct ObserverTraits {
  static void onNext(T) { /* Nope */ }
  static void onCompleted(T) { /* Nope */ }
};

template <typename T>
struct Observer {
  void onNext(T next) {
    ObserverTraits<T>::onNext(next);
  }
};

struct TestObservable : public ObservableTraits<int> {
  static void subscribe(const Observer<int>& observer)
  {
    observer.onNext(42);
    observer.onCompleted();
  }
};

struct TestObserver : public ObserverTraits<int> {
  static void onNext(int next) {
    std::cout << next << std::endl;
  }
  static void onCompleted() {
    std::cout << "Completed" << std::endl;
  }
};

int main()
{
  const TestObservable observable;
  const TestObserver observer;
  observable.subscribe(observer);
}

