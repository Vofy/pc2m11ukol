#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "data_read.h"
#include "database.h"

int main()
{
    FILE *input = fopen("zadani10_databaze.csv", "r");
    load_file(input, ';');
    fclose(input);

    /*struct Album *album2 = malloc(sizeof(struct Album));
    *album2 = (struct Album)
    {
        .name = "test",
        .author = "test",
        .genre = CLASSICAL,
        .year = 2005,
        .rating = 9
    };

    add_album(album2);*/

    char  c;
    while(!(c == 'Q' || c == 'q'))
    {
        if(c=='A' || c=='a')
        {
            struct Album *new_album = malloc(sizeof(struct Album));
            char genre[20];

            printf("\nNázev: ");
            scanf("%s", new_album->name);
            fflush(stdin);

            printf("\nInterpret: ");
            scanf("%s", new_album->author);
            fflush(stdin);

            printf("\nRok: ");
            scanf("%d", &new_album->year);
            fflush(stdin);

            printf("\nŽánr: ");
            scanf("%s", genre);
            fflush(stdin);

            printf("\nHodnocení: ");
            scanf("%f", &new_album->rating);
            fflush(stdin);

            new_album->genre = resolve_genre(genre);

            add_album(new_album);
        }

        if(c == 'D' || c == 'd')
        {
            int index;
            printf("\nZadejte index: ");
            scanf("%d", &index);
            fflush(stdin);
            remove_album(index);
        }

        if(c == 'E' || c == 'e')
        {
            FILE *output = fopen("output.csv", "w");
            export_to_csv(output);
            fclose(output);
        }

        if(c == 'P' || c == 'p')
            print_all();

        printf("\nA: Add, D: Delete, E: Export to CSV, P: Print, Q: Quit\n");
        scanf("%c", &c);
        fflush(stdin);
    }

    return 0;
}
