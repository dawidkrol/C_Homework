#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info {
    int len;
    int count;
};

void pierwsaFunkcja()
{
    //1.
    struct info i;
    printf("Ilosc lancuchow: ");
    scanf("%d",&i.count);
    printf("Przewidywana dlugosc najdluzszego lancucha: ");
    scanf("%d",&i.len);

    //2.
    char* pamiec = (char*)calloc( i.len * i.count,sizeof(char));

    //3.
    for (int j = 0; j < i.count; j++) {
        scanf("%s", (pamiec + (j * i.len)));
    }

    //4.
    int w = 1;
    while (w != 0) {
        w=0;
        for (int j = 0; j < i.count - 1; j++) {
            if (pamiec[j * i.len + i.len] < pamiec[j * i.len]) {
                w++;
                char tmp = pamiec[j * i.len + i.len];
                pamiec[j * i.len + i.len] = pamiec[j * i.len];
                pamiec[j * i.len] = tmp;
            }
        }
    }

    //5.
    for (int j = 0; j < i.count * i.len; j++) {
        if(j % i.len == 0)
            printf("\n");
        printf("%c",*(pamiec + j));
    }
}

char* wczytywanie()
{
    char a[1000];
    scanf("%s",a);
    int b = strlen(a);

    char* output = malloc(sizeof(char) * b);
    if(output == NULL)
    {
        exit(0);
    }
    strcpy(output,a);

    return output;

}

void drugafunkcja()
{
    //1.
    int liczba_lancuchow;
    printf("Liczba  łańcuchów, które będą wczytane: ");
    scanf("%d",&liczba_lancuchow);

    //2.
    char **w = malloc(liczba_lancuchow * sizeof(char*));

    //3.
    for (int i = 0; i < liczba_lancuchow; i++ ) {
        *(w + i) = wczytywanie();
    }

    //4.
    int k = 1;
    while (k != 0) {
        k=0;
        for (int j = 0; j < liczba_lancuchow - 1; j++) {
            if (**(w+1) < **w) {
                k++;
                char tmp = **(w+1);
                **(w+1) = **(w);
                **(w) = tmp;
            }
        }
    }

    //5.
    for (int i = 0; i < liczba_lancuchow; i++) {
        printf("%s\n",*(w + i));
    }
}

int main() {
    //pierwsaFunkcja();
    drugafunkcja();
    return 0;
}
