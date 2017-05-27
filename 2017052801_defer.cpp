#include <cassert>
#include <functional>

class Defer {
public:
    explicit Defer(const std::function<void()>& defered) noexcept
        : m_defered(defered)
    { }

    explicit Defer(std::function<void()>&& defered) noexcept
        : m_defered(defered)
    { }

    ~Defer()
    {
        m_defered();
    }
private:
    std::function<void()> m_defered;
};

class ShoudBeDestroyedManualy {
public:
    void Destroy()
    {
        m_destroyed = true;
    }

    ~ShoudBeDestroyedManualy()
    {
        assert(m_destroyed);
    }

private:
    bool m_destroyed = false;
};

int main()
{
    ShoudBeDestroyedManualy s;
    auto defer = Defer(
        [&]()
        {
            s.Destroy();
        }
    );
}
