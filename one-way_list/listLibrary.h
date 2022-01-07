//
// Created by Dawid on 06.01.2022.
//

#ifndef ONE_WAY_LIST_LISTLIBRARY_H
#define ONE_WAY_LIST_LISTLIBRARY_H

enum sort_type {unsorted,bySurname, byID};
struct El_listy {
    char* imie;
    char* nazwisko;
    int numerID;
    struct El_listy* next;
};
int ilosc_elementow(struct El_listy);
void asList(struct El_listy*, struct El_listy*, int);
void dodaj_element(struct El_listy, struct El_listy*);
void dodaj_element_poczatek(struct El_listy, struct El_listy*);
void AddAtEnd(struct El_listy, struct El_listy*);
struct El_listy sortBySurname(struct El_listy);
struct El_listy sortByID(struct El_listy);
void add_element_by_surname(struct El_listy, struct El_listy*);
void add_element_by_ID(struct El_listy, struct El_listy*);
int delete_element_id(int, struct El_listy*);
int saveToFile(struct El_listy *list, char *filename);
int addFromFile(struct El_listy *list, char *filename);
char* read();

#endif //ONE_WAY_LIST_LISTLIBRARY_H
