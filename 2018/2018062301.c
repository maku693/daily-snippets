#include <cstdint>

typedef struct {
  int32_t num;
} num_wrapper;

void num_wrapper_new(num_wrapper *nw) {
  nw->num = 0;
}

int main() {
  num_wrapper nw;
  num_wrapper_new(&nw);
}
