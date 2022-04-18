#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef enum
{
    UNKONWN=0,
    PUNK_ROCK,
    ROCK,
    METAL,
    FOLK,
    CLASSICAL,
    RAP
} Genre;

struct Album
{
    char         *name;
    char         *author;
    int           year;
    Genre         genre;
    float         rating;
    struct Album *next;
};

Genre resolve_genre(char *genre);
char *rev_resolve_genre(Genre genre);

#endif // TYPES_H_INCLUDED
