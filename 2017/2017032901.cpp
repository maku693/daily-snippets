#include <iostream>
#include <memory>

struct Runnable {
  struct Concept {
    virtual int run() const = 0;
  };

  template <class T>
  struct Holder : public Concept {
    T impl;
    Holder(T impl) : impl(impl) {}
    virtual int run() const override { return impl.run(); }
  };

  std::unique_ptr<Concept> runnable;

  template <class T>
  Runnable(T r) : runnable { new Holder<T>(r) } {}

  auto run() const { return this->runnable->run(); }
};

struct Foo {
  int run() const { return 42; }
};

struct Bar {
  int run() const { return 84; }
};

int main()
{
  Runnable runnables[] = { Foo(), Bar() };
  for (const auto& r : runnables) {
    std::cout << r.run() << std::endl;
  }
  
  return 0;
}

#include <iostream>
#include <memory>

template <class T>
struct Observable;

template <class T>
struct Observer;

template <class T>
struct AnonymousObserver;

template <class T>
struct Observable {
  virtual void subscribe(const Observer<T>&) const = 0;
  virtual void subscribe(
      std::function<void(const T&)> onNext,
      std::function<void(const std::runtime_error&)> onError,
      std::function<void()> onCompleted
  )
  {
    this->subscribe(AnonymousObserver<T>(onNext, onError, onCompleted));
  }
};

// TODO: use enable_if to make the argument of Observer::onNext to pass by value
// when it's type is fundamental
template <class T>
struct Observer {
  virtual void onNext(const T&) const = 0;
  virtual void onError(const std::runtime_error&) const = 0;
  virtual void onCompleted() const = 0;
};

template <class T>
struct AnonymousObserver : public Observer<T> {
  AnonymousObserver() = delete;
  AnonymousObserver(
    std::function<void(const T&)> onNext,
    std::function<void(const std::runtime_error&)> onError,
    std::function<void()> onCompleted
  ) : m_onNext(onNext)
    , m_onError(onError)
    , m_onCompleted(onCompleted)
  {}

  virtual void onNext(const int& next) const override
  {
    this->m_onNext(next);
  }

  virtual void onError(const std::runtime_error& error) const override
  {
    this->m_onError(error);
  }

  virtual void onCompleted() const override
  {
    this->m_onCompleted();
  }

  std::function<void(const T&)> m_onNext;
  std::function<void(const std::runtime_error&)> m_onError;
  std::function<void()> m_onCompleted;
};

struct Foo : Observable<int> {
  virtual void subscribe(const Observer<int>& observer) const override
  {
    observer.onNext(42);
    observer.onNext(84);
    observer.onCompleted();
  }
};

struct Bar : Observer<int> {
  virtual void onNext(const int& next) const override
  {
    std::cout << next << std::endl;
  }
  virtual void onError(const std::runtime_error&) const override {}
  virtual void onCompleted() const override
  {
    std::cout << "Completed" << std::endl;
  }
};

int main()
{
  Foo foo;
  Bar bar;

  foo.subscribe(bar);
  foo.subscribe(
    [](const int& next) { std::cout << next + 100 << std::endl; },
    [](const std::runtime_error& next) {},
    []() {}
  );
  
  return 0;
}

#include <iostream>
#include <memory>

struct Runnable {
  struct Concept {
    virtual int run() const = 0;
  };

  template <class T>
  struct Holder : public Concept {
    T impl;
    Holder(T impl) : impl(impl) {}
    virtual int run() const override { return impl.run(); }
  };

  std::unique_ptr<Concept> runnable;

  template <class T>
  Runnable(T r) : runnable { new Holder<T>(r) } {}

  auto run() const { return this->runnable->run(); }
};

struct Foo {
  int run() const { return 42; }
};

struct Bar {
  int run() const { return 84; }
};

int main()
{
  Runnable runnables[] = { Foo(), Bar() };
  for (const auto& r : runnables) {
    std::cout << r.run() << std::endl;
  }
  
  return 0;
}

