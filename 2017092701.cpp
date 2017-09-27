#include<iostream>

int multiply_two(int v)
{
  return v * 2;
}

int main()
{
  const int v = 1;
  const int expected = v * 2;
  const int actual = multiply_two(v);
  if (expected != actual) {
    std::cerr << "Value isn't multiplied."
  }
}
