#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    while (read != -1) {
        puts("enter a line");
        read = getline(&line, &len, stdin);
        printf("line = %s", line);
        printf("line length = %zu\n", read);
        puts("");
    }
    free(line);
    return 0;
}
