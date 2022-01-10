#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "listLibrary.h"
#include <string.h>

//Funkcja pomocnicza do czytania z klawiatury
char* read() {
    char b[100];
    scanf("%s",b);
    int i = strlen(b);
    char *output = malloc(i*sizeof(char));
    if(output == NULL) {
        exit(0);
    }
    strcpy(output,b);
    return output;
}

//Zwraca ilość elementów listy
int ilosc_elementow(struct El_listy list) {
    struct El_listy *temp = list.next;
    int output = 0;
    while (temp != NULL){
        temp = temp->next;
        output++;
    }
    return output;
}

//Przypisuje do argumentu l, ktory jest tablica elementow elementy listy
void asList(struct El_listy *list, struct El_listy *l, int c)
{
    for (int i = 0; i < c; i++) {
        list = list->next;
        l[i] = *list;
    }
}

//Dodaje element do listy za podanym w argumencie
void dodaj_element(struct El_listy student, struct El_listy *prev_elem){
    struct El_listy *new = malloc(sizeof(struct El_listy));
    new->imie = student.imie;
    new->nazwisko = student.nazwisko;
    new->numerID = student.numerID;
    new->next = NULL;
    prev_elem->next = new;
}

//Dodaje element na miejsce pierwszego elementu listy
void dodaj_element_poczatek(struct El_listy student, struct El_listy *list){
    if(list->next != NULL) {
        struct El_listy *new = malloc(sizeof(struct El_listy));
        struct El_listy *temp = malloc(sizeof(struct El_listy));
        memcpy(temp, list->next, sizeof(*list->next));
        new->imie = student.imie;
        new->nazwisko = student.nazwisko;
        new->numerID = student.numerID;
        new->next = temp;
        list->next = new;
    } else{
        dodaj_element(student,list);
    }
}

//Dodaje element na koncu listy
void AddAtEnd(struct El_listy student, struct El_listy *list){
    if(list->next == NULL)
    {
        dodaj_element(student,list);
    } else {
        while (list->next != NULL) {

            list = list->next;
        }
        dodaj_element(student, list);
    }
}

struct El_listy sortBySurname(struct El_listy list){
    int c = ilosc_elementow(list);

    struct El_listy l[c];

    asList(&list,l,c);

    int change = 1;

    while (change != 0)
    {
        change = 0;
        for (int i = 0; i < c-1; i++) {
            if(l[i].nazwisko[0] > l[i+1].nazwisko[0]){
                struct El_listy tmp = l[i];
                l[i] = l[i+1];
                l[i+1] = tmp;
                change++;
            }
        }
    }
    list.next = NULL;
    for (int i = 0; i < c; i++) {
        AddAtEnd(l[i],&list);
    }
    return list;
}

struct El_listy sortByID(struct El_listy list){
    int c = ilosc_elementow(list);

    struct El_listy l[c];

    asList(&list,l,c);

    int change = 1;

    while (change != 0)
    {
        change = 0;
        for (int i = 0; i < c-1; i++) {
            if(l[i].numerID > l[i+1].numerID){
                struct El_listy tmp = l[i];
                l[i] = l[i+1];
                l[i+1] = tmp;
                change++;
            }
        }
    }
    list.next = NULL;
    for (int i = 0; i < c; i++) {
        AddAtEnd(l[i],&list);
    }
    return list;
}

//Dodaje element i sortuje po nazwisku
void add_element_by_surname(struct El_listy student, struct El_listy *list) {
    AddAtEnd(student,list);
    *list = sortBySurname(*list);
}

//Dodaje element i sortuje po ID
void add_element_by_ID(struct El_listy student, struct El_listy *list)
{
    AddAtEnd(student,list);
    *list = sortByID(*list);
}

//Usuwa element o podanym id
int delete_element_id(int id, struct El_listy *list) {
    while (list != NULL){
        if(list->next->numerID == id)
        {
            list->next = list->next->next;
            return 1;
        }
        list = list->next;
    }
    return 0;
}

//Zapisuje liste do pliku
int saveToFile(struct El_listy *list, char *filename) {
    FILE* fp;

    fp=fopen(filename, "w");
    if (fp==NULL)
        return 0;

    list = list->next;
    while (list != NULL){
        fprintf(fp,"%s\n%s\n%d\n",list->imie,list->nazwisko,list->numerID);
        list = list->next;
    }
    fprintf(fp,"\0");

    fclose(fp);
    return 1;
}

//Funkcja do czytania i alokowania w pamieci wartosci z pliku
char* readFromFile(FILE *fp) {
    char b[100];
    fscanf(fp, "%s",b);
    int i = strlen(b);
    char *output = malloc(i*sizeof(char));
    strcpy(output,b);
    return output;
}

//Odczytuje liste z pliku
int addFromFile(struct El_listy *list, char *filename){
    FILE* fp;
    fp=fopen(filename, "r");
    if (fp==NULL)
        return 0;

    while (1) {
        struct El_listy e;
        for (int j = 1; j <= 3; j++) {
            if(j==1) {
                e.imie = readFromFile(fp);
            } else if(j==2) {
                e.nazwisko = readFromFile(fp);
            } else if(j==3){
                fscanf(fp, "%d",&e.numerID);
            }
        }
        if(e.imie[0] == '\0')
            break;
        AddAtEnd(e,list);
    }

    fclose(fp);
    return 1;
}