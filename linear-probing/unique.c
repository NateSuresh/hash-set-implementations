/*
 * File:        unique.c
 *
 * Copyright:   2021, Darren C. Atkinson
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "set.h"

# define MAX_SIZE 18000

static unsigned strhash(char *s)
{
    unsigned hash = 0;

    while (*s != '\0')
        hash = 31 * hash + *s ++;

    return hash;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[BUFSIZ], **elts, *word;
    SET *unique;
    int i, words;
    bool lflag = false;

    if (argc > 1 && strcmp(argv[1], "-l") == 0) {
        lflag = true;
        argc --;

        for (i = 1; i < argc; i ++)
            argv[i] = argv[i + 1];
    }

    if (argc == 1 || argc > 3) {
        fprintf(stderr, "usage: %s [-l] file1 [file2]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }

    words = 0;
    unique = createSet(MAX_SIZE, strcmp, strhash);

    while (fscanf(fp, "%s", buffer) == 1) {
        words ++;
        if (!findElement(unique, buffer))
            addElement(unique, strdup(buffer));
    }

    fclose(fp);

    if (!lflag) {
        printf("%d total words\n", words);
        printf("%d distinct words\n", numElements(unique));
    }

    if (argc == 3) {
        if ((fp = fopen(argv[2], "r")) == NULL) {
            fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[2]);
            exit(EXIT_FAILURE);
        }

        while (fscanf(fp, "%s", buffer) == 1) {
            if ((word = findElement(unique, buffer)) != NULL) {
                removeElement(unique, buffer);
                free(word);
            }
        }

        fclose(fp);

        if (!lflag)
            printf("%d remaining words\n", numElements(unique));
    }

    if (lflag) {
        elts = getElements(unique);

        for (i = 0; i < numElements(unique); i ++)
            printf("%s\n", elts[i]);

        free(elts);
    }

    destroySet(unique);
    exit(EXIT_SUCCESS);
}
