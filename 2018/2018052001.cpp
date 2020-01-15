template <class T>
mat<T, 3, 3> rotate(const vec<T, 3>& axis, T theta)
{
  const T& [x, y, z] = axis;
  const T st = std::sin(theta);
  const T ct = std::cos(theta);
  const T a = (1 - ct);

  return {
    x * x * a + ct,
    x * y * a - z * st,
    x * z * a + y * st,
    y * x * a + z * st,
    y * y * a + ct,
    y * z * a - x * st,
    z * x * a - y * st,
    z * y * a + x * st,
    z * z * a + ct,
  };
}
