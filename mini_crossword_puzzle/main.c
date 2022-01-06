#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct info {
    char *word;
    int len;
    char firstLetter;
    char lastLetter;
};

void skorowidzC(FILE *fp, int* skorowidz)
{
    int i = 0;
    char bufor[100], letter;
    long position = 1;
    while (ftell(fp) != position) {
        if(letter != bufor[0])
        {
            letter = bufor[0];
            skorowidz[i] = position;
            i++;
            printf("%c - %d\n",bufor[0],position);
        }
        position = ftell(fp);
        fgets(bufor, 100, fp);
        if(ftell(fp) == position){
            skorowidz[i] = ftell(fp);
            printf("END - %d\n",ftell(fp));
        }
    }
}

struct info losowanie(FILE *fp, char letter,int skorowidz[26])
{
    struct info output;
    int a = letter - 97, losowanie;
    char bufor[100];
    if(letter == ' ')
    {
        fseek(fp,0,SEEK_END);
        losowanie = rand() % ftell(fp);
    } else
    {
        losowanie = skorowidz[a] + rand() % skorowidz[a + 1];
    }
    fseek(fp, losowanie, SEEK_SET);

    for (int i = 0; i < 2; i++) {
        fgets(bufor,100, fp);
    }

    output.len = strlen(bufor);
    output.firstLetter = bufor[0];
    output.lastLetter = bufor[output.len-2];
    char *fw = (char *)malloc(sizeof(char) * output.len);
    strcpy(fw,bufor);
    output.word = fw;
    return output;

}

struct info firstWord(FILE *file,int skorowidz[26])
{
    struct info output;

    do {
        output = losowanie(file, ' ', skorowidz);
    } while (output.len < 3);

    return output;

}

struct info secondWord(FILE *fp,char fLetter, int skorowidz[26])
{
    struct info word;

    word = losowanie(fp,fLetter,skorowidz);

    return word;
}

struct info thirdWord(FILE *fp,char lLetter, int skorowidz[26], int len)
{
    struct info word;
    int i = 0;
    do {
        i++;
        if(i > 110000){
            word.word = NULL;
            break;
        }
        word = losowanie(fp,lLetter,skorowidz);
    } while (word.len != len);

    return word;
}

struct info fourthWord(FILE *fp,char fLetter, char lLetter, int skorowidz[26], int len)
{
    struct info word;

    int i = 0;

    do {
        i++;
        if(i > 110000){
            word.word = NULL;
            break;
        }
        word = losowanie(fp,fLetter,skorowidz);
    } while (word.len != len || word.lastLetter != lLetter);

    return word;
}

//void showStructure(struct info i)
//{
//    printf("%d %c %c %s",i.len,i.firstLetter,i.lastLetter,i.word);
//}

int main() {

    srand(time(0));
    int skorowidz[26];
    FILE *fp;
    fp = fopen("../slowa.txt","r");

    if(fp == NULL)
    {
        printf("Blad podczas odczytu pliku.");
        return -1;
    }

    skorowidzC(fp,skorowidz);

    //Pierwsze słowo
//    struct info i1 = firstWord(fp,skorowidz);
//
//    //Drugie słowo
//    struct info i2 = secondWord(fp,i1.firstLetter,skorowidz);
//
//    //Trzecie słowo
//    struct info i3 = thirdWord(fp,i2.lastLetter,skorowidz,i1.len);
//
//    //Czwarte słowo
//    struct info i4 = fourthWord(fp,i1.lastLetter,i3.lastLetter,skorowidz,i2.len);
//
//    fclose(fp);
//
//    if(i4.word == NULL || i3.word == NULL || i1.firstLetter != i2.firstLetter ||
//            i2.lastLetter != i3.firstLetter || i3.lastLetter != i4.lastLetter ||
//            i1.lastLetter != i4.firstLetter){
//        printf("Niepowodzenie!");
//        exit(0);
//    }
//
//    printf("%s",i1.word);
//    for (int i = 1; i < i2.len-2; i++) {
//        printf("%c",i2.word[i]);
//        for (int j = 0; j < i1.len-3; j++) {
//            printf(" ");
//        }
//        printf("%c\n",i4.word[i]);
//    }
//    printf("%s",i3.word);

    return 0;
}
