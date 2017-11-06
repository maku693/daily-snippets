#include <memory>

namespace mlisp {

enum class ObjectType {
    Atom,
    Pair,
};

template <ObjectType Type>
class Object {
public:
    constexpr ObjectType object_type = Type;

    virtual ~Object() {};
};

class Pair : public Object<ObjectType::Pair> {
    std::shared_ptr<Object> left;
    std::shared_ptr<Object> right;
};

enum class AtomType {
    Symbol,
    Number
};

template <AtomType Type>
class Atom : public Object<ObjectType::Atom> {
public:
    constexpr AtomType atom_type = Type;
};

class Symbol : public Atom<AtomType::Symbol> {};

class Number : public Atom<AtomType::Number> {
    double value;
};

} // namespace mlisp

int main()
{
    return 0;
}
