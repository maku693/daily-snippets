// This doesn't compile; the classes should be placed in separated source
// files.

class Size {
public:
    constexpr Size() noexcept
        : m_width(0)
        , m_height(0)
    { }

    constexpr Size(float width, float height) noexcept
        : m_width(width)
        , m_height(height)
    { }

    explicit constexpr Size(Point point) noexcept
        : m_width(point.getX())
        , m_height(point.getY())
    { }

    constexpr void setWidth(float width) noexcept
    {
        this->m_width = width;
    }

    constexpr void setHeight(float height) noexcept
    {
        this->m_height = height;
    }

    constexpr float getWidth() const noexcept
    {
        return this->m_width;
    }

    constexpr float getHeight() const noexcept
    {
        return this->m_height;
    }

private:
    float m_width;
    float m_height;
};

class Point {
public:
    constexpr Point() noexcept
        : m_x(0)
        , m_y(0)
    { }

    constexpr Point(float x, float y) noexcept
        : m_x(x)
        , m_y(y)
    { }

    explicit constexpr Point(Size size) noexcept
        : m_x(size.getWidth())
        , m_y(size.getHeight())
    { }

    constexpr void setX(float x) noexcept
    {
        this->m_x = x;
    }

    constexpr void setY(float y) noexcept
    {
        this->m_y = y;
    }

    constexpr float getX() const noexcept
    {
        return this->m_x;
    }

    constexpr float getY() const noexcept
    {
        return this->m_y;
    }

private:
    float m_x;
    float m_y;
};

class Rect {
    constexpr Rect() noexcept
        : m_origin({ })
        , m_size({ })
    {}

    constexpr Rect(Point origin, Size size) noexcept
        : m_origin(origin)
        , m_size(size)
    {}

    constexpr void setOrigin(Point origin) const noexcept
    {
         this->m_origin = origin;
    }

    constexpr void setSize(Size size) const noexcept
    {
         this->m_size = size;
    }

    constexpr Point getOrigin() const noexcept
    {
        return this->m_origin;
    }

    constexpr Size getSize() const noexcept
    {
        return this->m_size;
    }

private:
    Point m_origin;
    Size m_size;
};

