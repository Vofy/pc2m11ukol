#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

void print_all();
void export_to_csv(FILE *output);
void add_album(struct Album *album);
void remove_album(int index);
void sort_albums(Order order);

#endif // DATABASE_H_INCLUDED
