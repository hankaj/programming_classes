#include <stdio.h>
#define WYGRANA 10000
#define PRZEGRANA -10000

void wypisz(char pl[3][3]){
    int i, j;
    for (j=0; j<3; j++){
        for (i=0; i<3; i++)
            printf("%c", pl[j][i]);
        printf("\n");}
}

int ocena(char pl[3][3]){
    int i, j;
    int przegrana=1;
    int wygrana=0;
    for (j=0; j<3; j++) {
        for (i = 0; i < 3; i++)
            if (pl[j][i] != 'x') break;
        if (i==3) return WYGRANA;
    }
    for (j=0; j<3; j++) {
        for (i = 0; i < 3; i++)
            if (pl[j][i] != 'o') break;
        if (i==3) return PRZEGRANA;
    }
    for (j=0; j<3; j++) {
        for (i = 0; i < 3; i++)
            if (pl[i][j] != 'x') break;
        if (i==3) return WYGRANA;
    }
    for (j=0; j<3; j++) {
        for (i = 0; i < 3; i++)
            if (pl[i][j] != 'o') break;
        if (i==3) return PRZEGRANA;
    }
    for (i = 0; i < 3; i++)
        if (pl[i][i] != 'o') break;
    if (i==3) return PRZEGRANA;

    for (i = 0; i < 3; i++)
        if (pl[i][2-i] != 'o') break;
    if (i==3) return PRZEGRANA;

    for (i = 0; i < 3; i++)
        if (pl[i][i] != 'x') break;
    if (i==3) return WYGRANA;

    for (i = 0; i < 3; i++)
        if (pl[i][2-i] != 'x') break;
    if (i==3) return WYGRANA;

    return 0;
}

void wypisz_sytuacje(char pl[3][3]){
    int i, j, l, m;
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            if (pl[j][i]==' '){
                pl[j][i] = 'x';
//                wypisz(pl);
//                printf("%d\n", ocena(pl));
                for (l=0; l<3; l++)
                    for (m=0; m<3; m++)
                        if (pl[m][l]==' '){
                            pl[m][l] = 'o';
                            wypisz(pl);
                            printf("%d\n", ocena(pl));
                            pl[m][l] = ' ';
                        }
                pl[j][i] = ' ';
            }
}

int ruchy(char pl[3][3], int glebokosc, int *k, int *m){
    int niepot, tezniepot;
    int *ws1=&niepot,  *ws2=&niepot;
    int wmin = 1000000000;
    int wmax=-1000000000;
    int i, j, war, oc;
    oc=ocena(pl);
    if (glebokosc==0) return oc;
    if (oc==PRZEGRANA) return PRZEGRANA;
    if (oc==WYGRANA) return WYGRANA;
    if (glebokosc%2==0){
    for (i=0; i<3; i++){
        for (j=0; j<3; j++){
            if (pl[i][j]==' '){
                pl[i][j] = 'x';
                war=ruchy(pl, glebokosc-1, ws1, ws2);
                pl[i][j] = ' ';
            }
            if (war>=wmax) {wmax=war; *k=i; *m=j;}
        }
    }
    return wmax; }
    else {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (pl[i][j] == ' ') {
                    pl[i][j] = 'o';
                    war = ruchy(pl, glebokosc - 1, ws1, ws2);
                    pl[i][j] = ' ';
                }
                if (war <= wmin) {
                    wmin = war;
                }
            }
        }
        return wmin;
    }
}

int main() {
    char pl[3][3]={" xx"," o ","o  "};
    int i, j;
    int *k = &i;
    int *m = &j;
    ruchy(pl, 4, k, m);
    pl[i][j]='x';
    wypisz(pl);
    return 0;
}
