#include <stdio.h>

#define WYGRANA 1000
#define PRZEGRANA -1000



void wypisz(char pl[10][10]){
    int i, j;
    for (j=0; j<10; j++){
        for (i=0; i<10; i++)
            printf(" %c |", pl[j][i]);
        printf("\n---+---+---+---+---+---+---+---+---+---\n");}
}


int ocena(char pl[10][10]){
    int wyst[7] = {};
    int i, j, licznik, licznik2, licznik3, licznik4, wynik;

    for (i=0; i<10; i++){
        licznik=0;
        licznik2=0;
        licznik3=0;
        licznik4=0;
        for (j=0; j<10; j++){
            // rzędy
            if (pl[i][j]=='x') licznik++;
            else {wyst[licznik]++; licznik=0;}

            if (pl[i][j]=='o') licznik2++;
            else {wyst[licznik2]--; licznik2=0;}
//
//            //kolumny
//            if (pl[j][i]=='x') licznik3++;
//            else {wyst[licznik3]++; licznik3=0;}
//
//            if (pl[j][i]=='o') licznik4++;
//            else {wyst[licznik4]--; licznik=0;}

            if (j==9) {wyst[licznik2]--, wyst[licznik]++;} //wyst[licznik3]++; wyst[licznik4]--;}
        }
    }
//     // po kolumnach
//     for (i=0; i<10; i++){
//         licznik=0;
//         for (j=0; j<10; j++){
//             if (pl[j][i]=='x') licznik++;
//             else {wyst[licznik]++; licznik=0;}
//             if (j==9) wyst[licznik]++;
//         }
//     }
    //po rzędach kółka
//    for (i=0; i<10; i++){
//        licznik=0;
//        for (j=0; j<10; j++){
//            if (pl[i][j]=='o') licznik++;
//            else {wyst[licznik]--; licznik=0;}
//            if (j==9) wyst[licznik]--;
//        }
//    }
//     // po kolumnach kółka
//     for (i=0; i<10; i++){
//         licznik=0;
//         for (j=0; j<10; j++){
//             if (pl[j][i]=='o') licznik++;
//             else {wyst[licznik]--; licznik=0;}
//             if (j==9) wyst[licznik]--;
//         }
//     }
//     // po skosie prawy górny
//     for (i=0; i<9; i++){
//         licznik=0;
//         for (j=0; j<(10-i); j++){
//             if (pl[j][j+i]=='x') licznik++;
//             else {wyst[licznik]++; licznik=0;}
//             if (j==(10-i-1)) wyst[licznik]++;
//         }
//     }
//     // po skosie lewy dolny
//     for (i=1; i<9; i++){
//         licznik=0;
//         for (j=0; j<(10-i); j++){
//             if (pl[j+i][j]=='x') licznik++;
//             else {wyst[licznik]++; licznik=0;}
//             if (j==(10-i-1)) wyst[licznik]++;
//         }
//     }
//     // po skosie lewy górny
//     for (i=0; i<9; i++){
//         licznik=0;
//         for (j=0; j<(10-i); j++){
//             if (pl[j][9-i-j]=='x') licznik++;
//             else {wyst[licznik]++; licznik=0;}
//             if (j==(10-i-1)) wyst[licznik]++;
//         }
//     }
//     // po skosie prawy dolny
//     for (i=0; i<8; i++){
//         licznik=0;
//         for (j=(1+i); j<10; j++){
//             if (pl[j][10-j+i]=='x') licznik++;
//             else {wyst[licznik]++; licznik=0;}
//             if (j==9) wyst[licznik]++;
//         }
//     }
//     // po skosie prawy górny kółka
//     for (i=0; i<9; i++){
//         licznik=0;
//         for (j=0; j<(10-i); j++){
//             if (pl[j][j+i]=='o') licznik++;
//             else {wyst[licznik]--; licznik=0;}
//             if (j==(10-i-1)) wyst[licznik]--;
//         }
//     }
//     // po skosie lewy dolny kółka
//     for (i=1; i<9; i++){
//         licznik=0;
//         for (j=0; j<(10-i); j++){
//             if (pl[j+i][j]=='o') licznik++;
//             else {wyst[licznik]--; licznik=0;}
//             if (j==(10-i-1)) wyst[licznik]--;
//         }
//     }
//     // po skosie lewy górny kółka
//     for (i=0; i<9; i++){
//         licznik=0;
//         for (j=0; j<(10-i); j++){
//             if (pl[j][9-i-j]=='o') licznik++;
//             else {wyst[licznik]--; licznik=0;}
//             if (j==(10-i-1)) wyst[licznik]--;
//         }
//     }
//     // po skosie prawy dolny kółka
//     for (i=0; i<8; i++){
//         licznik=0;
//         for (j=(1+i); j<10; j++){
//             if (pl[j][10-j+i]=='o') licznik++;
//             else {wyst[licznik]--; licznik=0;}
//             if (j==9) wyst[licznik]--;
//         }
//     }
////
//    for (i=2; i<6; i++) printf("%d ", wyst[i]);
//    printf("\n");
    if (wyst[5]>0) return WYGRANA;
    if (wyst[5]<0) return PRZEGRANA;
    wynik = wyst[2] + wyst[3]*5 + wyst[4]*20; //+ wyst[5]*1000;
    return wynik;
}

int ruchy(char pl[10][10], int glebokosc, int *k, int *m){
    int niepot;
    int wmin = 1000000000;
    int wmax= -1000000000;
    int i, j, war, oc;;
    oc=ocena(pl);
    if (glebokosc==0) return oc;
    if (oc==PRZEGRANA) return PRZEGRANA;
    if (oc==WYGRANA) return WYGRANA;
    if (glebokosc%2==0){
        for (i=0; i<10; i++){
            for (j=0; j<10; j++){
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
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
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
    char pl[10][10]={"          ","          ","          ", "          ", "          ", "          ","          ","          ", "          ", "          "};
    int i, j, x, y;
    int *k = &i;
    int *m = &j;
//    ruchy(pl, 4, k, m);
//    pl[i][j]='x';
//    wypisz(pl);
//    if (ocena(pl)==WYGRANA) {printf("Komputer wygrał\n");}
//    wypisz(pl);
//    printf("%d\n", ocena(pl));

    while(1) {
        ruchy(pl, 4, k, m);
//        printf("tu ocena: %d\n",ruchy(pl, 4, k, m));
        printf("Ruch komputera:\n");
        pl[i][j]='x';
        wypisz(pl);

        if (ocena(pl)==WYGRANA) {printf("Komputer wygrał\n"); break;}

        while (1) {
            printf("Podaj ruch\n");
            scanf("%d %d", &x, &y);
            if (pl[x][y]==' ') {pl[x][y] = 'o'; break;}
            else printf("Miejsce zajęte\n");
        }

        wypisz(pl);
        if (ocena(pl)==PRZEGRANA) {printf("Wygrałeś!\n"); break;}
    }
}

