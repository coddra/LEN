#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void process(char* text) {
    FILE* f = fopen("tmp.s", "w");
    fputs(text, f);
    fputs("\n", f);
    fclose(f);

    int res = system("as tmp.s -o tmp.o");
    if (res) {
        printf("error: as returned exit status %d\n", res);
        return;
    }

    char* buffer = malloc(999);
    f = popen("objdump -d tmp.o", "r");
    buffer[fread(buffer, sizeof(*buffer), 999, f)] = '\0';
    pclose(f);

    int scount = 0;
    int i = 0;
    for ( ; scount < 4; i++)
        if (buffer[i] == ':')
            scount++;
    char* tmp = (char*)((long)buffer + i + 1);
    for (i = 0; i < strlen(tmp); i++)
        if (tmp[i] == '\t')
            tmp[i] = 0;
    puts(tmp);
    free(buffer);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        char* prompt = "(len) ";
        char* tmp = NULL;
        size_t l = 0;
        fputs(prompt, stdout);
        getline(&tmp, &l, stdin);
        while (strcmp(tmp, "q\n")) {
            if (strcmp(tmp, "\n"))
                process(tmp);
            free(tmp);
            tmp = NULL;
            fputs(prompt, stdout);
            getline(&tmp, &l, stdin);
        }
        free(tmp);
    } else {
        char* tmp = malloc(2);
        tmp[0] = '\t';
        tmp[1] = 0;
        tmp = strcat(tmp, argv[1]);
        for (int i = 2; i < argc; i++) {
            tmp = strcat(tmp, " ");
            tmp = strcat(tmp, argv[i]);
        }
        process(tmp);
        free(tmp);
    }
}
