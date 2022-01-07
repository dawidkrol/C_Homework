#include <stdio.h>
#include <stdlib.h>
#include "listLibrary.h"

//Wypisuje na ekran elementy listy
void readFromList(struct El_listy *lista)
{
    lista = lista->next;
    while (lista != NULL){
        printf("%s %s %d\n",lista->imie,lista->nazwisko,lista->numerID);
        lista = lista->next;
    }
}

//Czyta dane do elementu listy
struct El_listy readData() {
    struct El_listy output;
    char s[100];

    printf("Wprowadz imie: ");
    output.imie = read();

    printf("\nWprowadz nazwisko: ");
    output.nazwisko = read();

    printf("\nWprowadz nr studenta: ");
    int c;
    scanf("%d",&c);
    output.numerID = c;

    return output;
}

void chosenA(enum sort_type *st, struct El_listy *el) {
    printf("Gdzie dodac element?\n'f' na poczatku listy\n'e' na koncu listy\n");

    //Wstawianie elementów według porządku jest możliwy po wcześniejszym posortowaniu
    if(*st == bySurname) {
        printf("'a' zachowujac porzadek alfabetyczny nazwisk\n");
    }
    else if(*st == byID) {
        printf("'n' zachowujac uporzadkowanie wg numeru ID");
    }


    //Podczas dodawania na początku lub na końcu listy lista oznaczana jest jako nieposortowana

    char c;
    scanf("%s",&c);
    switch (c) {
        case 'f':
            dodaj_element_poczatek(readData(),el);
            *st = unsorted;
            break;
        case 'e':
            AddAtEnd(readData(),el);
            *st = unsorted;
            break;
        default:
            if(*st == bySurname && c == 'a'){
                add_element_by_surname(readData(),el);
            }
            if(*st == byID && c == 'n'){
                add_element_by_ID(readData(),el);
            }
    }
}

enum sort_type chosenS(struct El_listy *el) {
    printf("'i' - posortuj wedlug numeru ID\n's' - posortuj wedlug nazwiska\n");
    enum sort_type ss = unsorted;
    char c;
    scanf("%s",&c);

    switch (c) {
        case 'i':
            *el = sortByID(*el);
            return byID;
        case 's':
            *el = sortBySurname(*el);
            return  bySurname;
    }
}

//Wypisuje na ekran status usuniecia elementu listy
void del_item(struct El_listy *el) {
    int id;
    printf("Podaj id studenta do usuniecia: ");
    scanf("%d",&id);
    if(delete_element_id(id,el)){
        printf("Usunieto element o id: %d", id);
    }
    else{
        printf("Nie znaleziono elementu o id = %d", id);
    }
}

int main() {
    enum sort_type *st = malloc(sizeof(enum sort_type));
    *st = unsorted;
    struct El_listy *start = NULL;
    char c, filename[15] = "nazwapliku.txt\0";

    do {
        printf("'a' - dodaj element\n");
        printf("'o' - odczytaj z pliku\n");
        if(start != NULL)
            printf("'d' - usun element o okreslonym numerze albumu\n'p' - pokaz wszystkie elementy listy\n's' - posortuj\n'z' - zapisz do pliku\n");
        printf("'x' - zakoncz program\n");
        scanf("%s", &c);
        switch (c) {
            case 'a':
                if(start == NULL)
                    start = calloc(1,sizeof(struct El_listy));
                chosenA(st, start);
                break;
            case 'o':
                if(start == NULL)
                    start = calloc(1,sizeof(struct El_listy));
                addFromFile(start,filename);
                break;
            default:
                if(start != NULL) {
                    if(c == 'd')
                        del_item(start);
                    if(c == 's')
                        *st = chosenS(start);
                    if(c == 'p')
                        readFromList(start);
                    if(c == 'z')
                        printf("%d", saveToFile(start,filename));
                }
                break;
        }
        printf("\n");
    } while (c != 'x');


    return 0;
}
