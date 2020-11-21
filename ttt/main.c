#include <stdio.h>
#define WYGRANA 10000
#define PRZEGRANA -10000

void wypisz(char pl[3][3]){
    int i, j;
    for (j=0; j<3; j++){
        for (i=0; i<3; i++)
            printf(" %c |", pl[j][i]);
        printf("\n---+---+---+\n");}
}

int ocena(char pl[3][3]){
    int i, j;

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
    int niepot;
    int wmin = 1000000000;
    int wmax=-1000000000;
    int i, j, war, oc;
    oc=ocena(pl);
    if ((glebokosc==0) || (oc==PRZEGRANA) || (oc==WYGRANA)) return oc;

    if (glebokosc%2==0){
    for (i=0; i<3; i++){
        for (j=0; j<3; j++){
            if (pl[i][j]==' '){
                pl[i][j] = 'x';
                war=ruchy(pl, glebokosc-1, &niepot, &niepot);
                pl[i][j] = ' ';
                if (war>wmax) {wmax=war; *k=i; *m=j;}
            }
        }
    }
        if (wmax>-1000000000) return wmax;
        return oc;
    }
    else {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (pl[i][j] == ' ') {
                    pl[i][j] = 'o';
                    war = ruchy(pl, glebokosc - 1, &niepot, &niepot);
                    pl[i][j] = ' ';
                    if (war < wmin) {wmin = war;}
                }
            }
        }
        if (wmin<1000000000) return wmin;
        return oc;
    }
}

int main() {
    char pl[3][3]={"   ","   ","   "};
    int i, j, x, y, counter=5;
    int *k = &i;
    int *m = &j;
    while(counter) {
        ruchy(pl, 10, k, m);
        printf("Ruch komputera:\n");
        pl[i][j]='x';
        wypisz(pl);

        if (ocena(pl)==WYGRANA) {printf("Komputer wygrał\n"); break;}
        if (counter==1) {printf("Remis"); break;}

        while (1) {
        printf("Podaj ruch\n");
        scanf("%d %d", &x, &y);
        if (pl[x][y]==' ') {pl[x][y] = 'o'; break;}
        else printf("Miejsce zajęte\n");
        }

        wypisz(pl);
        if (ocena(pl)==PRZEGRANA) {printf("Wygrałeś!\n"); break;}
        counter--;
    }
    return 0;
}
