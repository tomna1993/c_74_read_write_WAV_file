#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGV_LENGTH 100

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf ("Usage: <program> <input> <output> <factor>\n");
        return EXIT_FAILURE;
    }

    char input[MAX_ARGV_LENGTH] = { "" };
    char output[MAX_ARGV_LENGTH] = { "" };
    char factor[MAX_ARGV_LENGTH] = { "" };

    strcpy_s (input, MAX_ARGV_LENGTH, argv[1]);
    strcpy_s (output, MAX_ARGV_LENGTH, argv[2]);
    strcpy_s (factor, MAX_ARGV_LENGTH, argv[3]);

    // Open audio file
    FILE *fp = fopen(input, "rb");

    if (fp == NULL)
    {
        printf ("File cannot be opened!\n");
        return EXIT_FAILURE;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}