#include<stdlib.h>

int main(int argc, char** argv){
if (argc < 2) return -1;
const char* program = argv[1];
char* buf = calloc(100000, sizeof(char));
for (size_t i = 0; i < strlen(program); i++) {}
free(buf);
return 0;
}
