#include <stdlib.h>

int main()
{
  char* buf = calloc(1024, sizeof(char));
  free(buf);
}
