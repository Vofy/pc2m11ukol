#ifndef DATA_READ_H_INCLUDED
#define DATA_READ_H_INCLUDED

Genre resolve_genre(char *genre);
char *rev_resolve_genre(Genre genre);
int count_lines(FILE *file);
int load_file(FILE *input, char SEPARATOR);

#endif // DATA_READ_H_INCLUDED
