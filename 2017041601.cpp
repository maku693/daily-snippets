template <class T, class U>
struct Cell;

struct T;
struct Nil;

struct Symbol;

namespace Op {

struct Cond;
struct Define;
struct Lambda;
struct Quote;

}

namespace Func {

struct Atom;
struct Eq;

}

struct Env;

template <class T>
auto eval(Env&, const T&) -> decltype(auto);

template <class T, class U>
auto apply(Env&, const T&, const U&) -> decltype(auto);
