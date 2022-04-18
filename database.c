#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "data_read.h"

struct Album *head;
struct Album *tail;

struct Album *sorted;

void print_all()
{
    if(!head)
    {
        printf("No songs found\n\n");
        return;
    }

    struct Album *current = head;

    printf("%3s %40s %30s %10s %10s %10s\n\n", "ID", "Album", "Author", "Year", "Genre", "Rating");

    int index = 0;
    while(current)
    {
        printf("%3d %40s %30s %10d %10s %10.1f\n",
               index,
               current->name,
               current->author,
               current->year,
               rev_resolve_genre(current->genre),
               current->rating);

        current = current->next;
        index++;
    }

    printf("\n\n");
}

void export_to_csv(FILE *output)
{
    fseek(output, 0, SEEK_SET);

    fprintf(output, "Album;Interpret;Rok;Zanr;Hodnoceni\n");
    struct Album *current = head;

    while(current)
    {
        fprintf(output, "%s;%s;%d;%s;%f\n",
               current->name,
               current->author,
               current->year,
               rev_resolve_genre(current->genre),
               current->rating);

        current = current->next;
    }
}


void add_album(struct Album *album)
{
    // Pokud je záznam první
    if(!head || !tail)
    {
        head = album;
        tail = album;
    }

    // V bázi jsou už záznamy
    else
    {
        struct Album *prev, *next = head;

        // Po dokončení cyklu budou ukazatele ukazovat na budouci predchozi a nasledujici uzel
        while(next && album->rating <= next->rating)
        {
            prev = next;
            next = next->next;
        }

        if(!prev) // Zaznam bude zařazený na začátek spojovaného seznamu
        {
            head = album;
            album->next = next;
        }
        else if(!next) // Zaznam bude zařazený na konec spojovaného seznamu
        {
            prev->next = album;
            tail = album;
        }
        else // Zaznam bude uvnitř spojovaného seznamu
        {
            prev->next = album;
            album->next = next;
        }
    }
}

void remove_album(int index)
{
    struct Album *current = head;

    if(index == 0)
    {
        free(head);
        head = head->next;
    }
    else
    {
        for(int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }

        free(current->next);
        current->next = current->next->next;

        if(current->next == tail)
            tail = current->next->next;
    }
}

void sorted_insert(struct Album* newnode, Order order)
{
    if (sorted == NULL || sorted->rating >= newnode->rating) {
        newnode->next = sorted;
        sorted = newnode;
    }
    else {
        struct Album *current = sorted, *prev = NULL;

        if(order == ORDER_ASC)
        {
            while (current->next != NULL && current->next->rating < newnode->rating) {
                current = current->next;
            }
            newnode->next = current->next;
            current->next = newnode;
        }
        else if(order == ORDER_DESC)
        {
            while (current->next != NULL && current->next->rating > newnode->rating) {
                prev = current;
                current = current->next;
            }
            newnode->next = prev;
            prev->next = newnode;
        }
    }
}

// function to sort a singly linked list
// using insertion sort
void sort_albums(Order order)
{
    struct Album* current = head;

    // Traverse the given linked list and insert every
    // node to sorted
    while (current != NULL) {

        // Store next for next iteration
        struct Album* next = current->next;

        // insert current in sorted linked list
        sorted_insert(current, order);

        // Update current
        current = next;
    }
    // Update head to point to sorted linked list
    head = sorted;
}
