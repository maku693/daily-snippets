#include <stdio.h>

int main(int argc, char** argv)
{
    for (int i = 0; i < argc; i++) {
        int rc = puts(argv[i]);

        if (rc == EOF) {
            perror("Failed to put string.");
        }
    }

    return 0;
}
