int test_one_equal_one() {
  int e = 0;
  e += (1 == 1) ? 0 : 1;
  return e;
}

int main() {
  int error = 0;
  error += test_one();
  return error;
}
