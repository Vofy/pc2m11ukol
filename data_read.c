#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "database.h"

#define NEW_LINE '\n'
#define END_OF_LINE 1

unsigned int lines = 0;

char *get_file_header(FILE *input)
{
    char *file_header = malloc(128 * sizeof(char));
    fseek(input, 0, SEEK_SET);

    if(file_header)
    {
        char c;
        int file_header_index = 0;

        do
        {
            c = fgetc(input);
            file_header[file_header_index++] = c;
        }
        while (c != '\n');

        file_header[file_header_index] = '\0';
    }

    return file_header;
}

void count_lines(FILE *input)
{
    char c;
    int lines = 0;

    do
    {
        c = fgetc(input);
        if(c == '\n') lines++;
    }
    while (c != EOF);

    fseek(input, 0, SEEK_SET);
}

int load_file(FILE *input, char SEPARATOR)
{
    char c;

    char buffer[256];              // Buffer pro jednotliva pole
    int buffer_index = 0;
    int attribute_index = 0;

    struct Album *album = malloc(sizeof(struct Album));

    get_file_header(input);

    do
    {
        c = fgetc(input);

        if(c == SEPARATOR || c == NEW_LINE || c == EOF)
        {
            buffer[buffer_index] = '\0';

            switch(attribute_index)
            {
            case 0:
                char *name = malloc(strlen(buffer) * sizeof(album->name));
                strncpy(name, buffer, strlen(buffer));
                album->name = name;
            case 1:
                char *author = malloc(strlen(buffer) * sizeof(album->author));
                strncpy(author, buffer, strlen(buffer));
                album->author = author;
            case 2:
                album->year = atoi(buffer);
            case 3:
                album->genre = resolve_genre(buffer);
            case 4:
                char *dot_ptr = strchr(buffer, ',');
                if(dot_ptr) *dot_ptr = '.';
                album->rating = atof(buffer);
            }

            buffer_index = 0;

            if(c == SEPARATOR)
            {
                attribute_index++;
            }
            else if(c == NEW_LINE || c == EOF)
            {
                add_album(album);

                attribute_index = 0;
                album = malloc(sizeof(struct Album));
            }
        }
        else
        {
            buffer[buffer_index++] = c;
        }
    }
    while (c != EOF);

    return 0;
}
