struct vec2  {
    float x = 0.0f;
    float y = 0.0f;
};

constexpr float dot(const vec2& lhs, const vec2& rhs) noexcept
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

int main()
{
    vec2 v1{ 2.0, 0.0 };
    vec2 v2{ 0.0, 1.0 };
    return static_cast<int>(dot(v1, v2));
}