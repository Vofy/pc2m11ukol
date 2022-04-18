#include <stdlib.h>
#include <string.h>

#include "types.h"

Genre resolve_genre(char *genre)
{
    if(!strcmp(genre, "Punk Rock")) return PUNK_ROCK;
    if(!strcmp(genre, "Rock"))      return ROCK;
    if(!strcmp(genre, "Metal"))     return METAL;
    if(!strcmp(genre, "Folk"))      return FOLK;
    if(!strcmp(genre, "Classical")) return CLASSICAL;
    if(!strcmp(genre, "Rap"))       return RAP;
    /* DEFAULT */                   return UNKONWN;
}

char *rev_resolve_genre(Genre genre)
{
    char *result = malloc(10 * sizeof(char));

    switch(genre) {
        case PUNK_ROCK: result = "Punk Rock"; break;
        case ROCK:      result = "Rock";      break;
        case METAL:     result = "Metal";     break;
        case FOLK:      result = "Folk";      break;
        case CLASSICAL: result = "Classical"; break;
        case RAP:       result = "Rap";       break;
        default:        result = "Unknown";   break;
    }

    return result;
}
