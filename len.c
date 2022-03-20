#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        puts("error: no input specified");
        return 1;
    }

    char* tmp = malloc(2);
    tmp[0] = '\t';
    tmp[1] = 0;
    tmp = strcat(tmp, argv[1]);
    tmp = strcat(tmp, "\t");
    for (int i = 2; i < argc; i++) {
        tmp = strcat(tmp, argv[i]);
        tmp = strcat(tmp, i == argc - 1 ? "\n" : " ");
    }

    FILE* f = fopen("tmp.s", "w");
    fputs(tmp, f);
    fclose(f);
    free(tmp);

    int res = system("as tmp.s -o tmp.o");
    if (res) {
        printf("error: as returned exit status %d", res);
        return 1;
    }

    char buffer[999];
    f = popen("objdump -d tmp.o", "r");
    buffer[fread(buffer, sizeof(*buffer), sizeof(buffer), f)] = '\0';
    pclose(f);

    int scount = 0;
    int i = 0;
    for ( ; scount < 4; i++)
        if (buffer[i] == ':')
            scount++;
    puts((char*)((long)buffer + i));
}
