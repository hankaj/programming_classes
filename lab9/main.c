#include <stdio.h>
#include <memory.h>
#include <limits.h>

void zmien_nazwe(char lista_plikow[10][10], char prefix[20]){
    int i=0;
    char nazwa_pliku[10], nowa_nazwa_pliku[20];
    while (lista_plikow[i]){
        strcpy(nazwa_pliku, lista_plikow[i]);
        strcpy(nowa_nazwa_pliku, prefix);
        strcat(nowa_nazwa_pliku, nazwa_pliku);
        rename(nazwa_pliku, nowa_nazwa_pliku);
        i++;
    }
}

int main() {
    int liczby[8] = {1,2,4, 256, INT_MAX, 0, -1, INT_MIN};
    char linia[100], temp[100];
    char *pos;
    int index=0;
    char slowo[6]={"kości"};
    char slowo2[6]={"Hania"};
    char slowonowe[6]={"H***a"};
    FILE *wsk, *wsk2, *wsk3, *wsk4, *wsk5, *wsk6, *wsk7, *wsk8, *pom, *wsk9;
    int w, i, zm1, suma=0, wiek1;
    char imie[10];
    char c;
    wsk = fopen("einstein.txt", "w");
    if (wsk==0) printf("blad otwarcia");
    else {
        w = fprintf(wsk, "“Jestem przekonany, że Bóg nie gra w kości”.");
        fclose(wsk);
    }
    wsk2 = fopen("einstein.txt", "a");
    if (wsk2==0) printf("blad otwarcia");
    else {
        w = fprintf(wsk2, "“Wszyscy jesteśmy ignorantami, ale każdy w czymś innym.”");
        fclose(wsk2);
    }
    wsk3 = fopen("randnum.txt", "r");
    if (wsk3==0) printf("blad otwarcia");
    else {
        for (i=0; i<10; i++) {
            w = fscanf(wsk3, "%d\n", &zm1);
            if (w) suma+=zm1;
        }
        printf("srednia: %d\n", suma/10);
        fclose(wsk3);
    }
    wsk4 = fopen("randnum2.txt", "r");
    if (wsk4==0) printf("blad otwarcia");
    else {
        for (i=0; i<10; i++) {
            fgets(linia, 100, wsk4);
            w = sscanf(linia, "%d\n", &zm1);
            if (w) printf("%d\n", zm1);
            else i--;
        }
        fclose(wsk4);
    }
//    wsk5 = fopen("plik.txt", "r");
//    if (wsk5==0) fprintf(stderr, "%s", "Blad otwarcia");
//    else {
//        c = fgetc(wsk5);
//        while (c != EOF) {
//            printf ("%c", c);
//            c = fgetc(wsk5);
//        }
//        fclose(wsk5);
//    }
    wsk6 = fopen("imiewiek.txt", "r");
    if (wsk6==0) fprintf(stderr, "%s", "Blad otwarcia");
    else {
        w = fscanf(wsk6, "Jestem %s i mam %d lat", imie, &wiek1);
        if (w) printf("%s %d\n", imie, wiek1);
        fclose(wsk6);
    }
    wsk7 = fopen("einstein.txt", "r");
    if (wsk7==0) fprintf(stderr, "%s", "Blad otwarcia");
    else {
        w=0;
        while(fgets(linia, 100, wsk7) != NULL){
            if (strstr(linia, slowo) != NULL) {w=1; break;}
        }
        fclose(wsk6);
        if (w) remove("einstein.txt");
    }
    wsk8 = fopen("imiewiek.txt", "r");
    pom = fopen("imiewiekpom.txt", "w");
    if (wsk8==0 || pom==0) fprintf(stderr, "%s", "Blad otwarcia");
    else {
        while(fgets(linia, 100, wsk8) != NULL) {
            if ((pos = strstr(linia, slowo2)) != NULL) {
                strcpy(temp, linia);
                index = pos - linia;
                linia[index]='\0';
                strcat(linia, slowonowe);
                strcat(linia, temp + index + 5);
            }
            fputs(linia, pom);
        }
        fclose(wsk8);
        fclose(pom);
        remove("imiewiek.txt");
        rename("imiewiekpom.txt", "imiewiek.txt");
    }

    char lista_plikow[10][10]={"x.txt", "y.txt"};
    //zmien_nazwe(lista_plikow, "pre");

    wsk9 = fopen("binaryfile", "wb");
    if (wsk9==0) fprintf(stderr, "%s", "Blad otwarcia");
    else {
//        for (i=0; i<8; i++){
//            fprintf(wsk9, "%d", liczby[i]);
//        }
        fprintf(wsk9, "tekst");l
        fclose(wsk9);
    }
}