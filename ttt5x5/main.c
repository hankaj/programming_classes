#include <stdio.h>

#define WYGRANA 1000
#define PRZEGRANA -1000

void wypisz(char pl[10][10]){
    int i, j;
    for (j=0; j<10; j++){
        for (i=0; i<10; i++)
            printf(" %c |", pl[j][i]);;
        printf("\n---+---+---+---+---+---+---+---+---+---\n");}
}

//int ocena(char pl[10][10]){
//    int i, j, counter, wynik;
//    wynik = 0;
//    // sprawdzanie w rzędach
//    for (i=0; i<10; i++){
//        for (j=0; j<10; j++){
//            // czy są dwójki
//            if (j<9) {
//                if (j==0 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]!='x') wynik+=1;
//                if (j==8 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j-1]!='x') wynik+=1;
//                if (j!=0 && j!=8 && pl[i][j-1]!='x' && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]!='x') wynik+=1;
//                if (j==0 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]!='o') wynik-=1;
//                if (j==8 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j-1]!='o') wynik-=1;
//                if (j!=0 && j!=8 && pl[i][j-1]!='o' && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]!='o') wynik-=1;
//            }
//            // czy są trójki
//            if (j<8) {
//                if (j==0 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]!='x') wynik+=5;
//                if (j==7 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j-1]!='x') wynik+=5;
//                if (j!=0 && j!=7 && pl[i][j-1]!='x' && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]!='x') wynik+=5;
//                if (j==0 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]!='o') wynik-=5;
//                if (j==7 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j-1]!='o') wynik-=5;
//                if (j!=0 && j!=7 && pl[i][j-1]!='o' && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]!='o') wynik-=5;
//            }
//            // czy są czwórki
//            if (j<7) {
//                if (j==0 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]!='x') wynik+=20;
//                if (j==6 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j-1]!='x') wynik+=20;
//                if (j!=0 && j!=6 && pl[i][j-1]!='x' && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]!='x') wynik+=20;
//                if (j==0 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]!='o') wynik-=20;
//                if (j==6 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j-1]!='o') wynik-=20;
//                if (j!=0 && j!=6 && pl[i][j-1]!='o' && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]!='o') wynik-=20;
//            }
//            // czy są piątki
//            if (j<6) {
//                if (j==0 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]=='x' && pl[i][j+5]!='x') wynik+=WYGRANA;
//                if (j==5 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]=='x' && pl[i][j-1]!='x') wynik+=WYGRANA;
//                if (j!=0 && j!=5 && pl[i][j-1]!='x' && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]=='x' && pl[i][j+5]!='x') wynik+=WYGRANA;
//                if (j==0 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]=='o' && pl[i][j+5]!='o') wynik+=PRZEGRANA;
//                if (j==5 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]=='o' && pl[i][j-1]!='o') wynik+=PRZEGRANA;
//                if (j!=0 && j!=5 && pl[i][j-1]!='o' && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]=='o' && pl[i][j+5]!='o') wynik+=PRZEGRANA;
//            }
//        }
//    }
//    // sprawdzanie w kolumnach
//    for (i=0; i<10; i++){
//        for (j=0; j<10; j++){
//            // czy są dwójki
//            if (j<9) {
//                if (j==0 && pl[j][i]=='x' && pl[j+1][i]=='x' && pl[j+2][i]!='x') wynik+=1;
//                if (j==8 && pl[j][i]=='x' && pl[j+1][i]=='x' && pl[j-1][i]!='x') wynik+=1;
//                if (j!=0 && j!=8 && pl[j-1][i]!='x' && pl[j][i]=='x' && pl[j+1][i]=='x' && pl[j+2][i]!='x') wynik+=1;
//                if (j==0 && pl[j][i]=='o' && pl[j+1][i]=='o' && pl[j+2][i]!='o') wynik-=1;
//                if (j==8 && pl[j][i]=='o' && pl[j+1][i]=='o' && pl[j-1][i]!='o') wynik-=1;
//                if (j!=0 && j!=8 && pl[j-1][i]!='o' && pl[j][i]=='o' && pl[j+1][i]=='o' && pl[j+2][i]!='o') wynik-=1;
//            }
//            // czy są trójki
//            if (j<8) {
//                if (j==0 && pl[j][i]=='x' && pl[j+1][i]=='x' && pl[j+2][i]=='x' && pl[j+3][i]!='x') wynik+=5;
//                if (j==7 && pl[j][i]=='x' && pl[j+1][i]=='x' && pl[j+2][i]=='x' && pl[j-1][i]!='x') wynik+=5;
//                if (j!=0 && j!=7 && pl[j-1][i]!='x' && pl[j][i]=='x' && pl[j+1][i]=='x' && pl[j+2][i]=='x' && pl[j+3][i]!='x') wynik+=5;
//                if (j==0 && pl[j][i]=='o' && pl[j+1][i]=='o' && pl[i][j+2]=='o' && pl[i][j+3]!='o') wynik-=5;
//                if (j==7 && pl[j][i]=='o' && pl[j+1][i]=='o' && pl[i][j+2]=='o' && pl[i][j-1]!='o') wynik-=5;
//                if (j!=0 && j!=7 && pl[i][j-1]!='o' && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]!='o') wynik-=5;
//            }
//            // czy są czwórki
//            if (j<7) {
//                if (j==0 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]!='x') wynik+=20;
//                if (j==6 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j-1]!='x') wynik+=20;
//                if (j!=0 && j!=6 && pl[i][j-1]!='x' && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]!='x') wynik+=20;
//                if (j==0 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]!='o') wynik-=20;
//                if (j==6 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j-1]!='o') wynik-=20;
//                if (j!=0 && j!=6 && pl[i][j-1]!='o' && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]!='o') wynik-=20;
//            }
//            // czy są piątki
//            if (j<6) {
//                if (j==0 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]=='x' && pl[i][j+5]!='x') wynik+=WYGRANA;
//                if (j==5 && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]=='x' && pl[i][j-1]!='x') wynik+=WYGRANA;
//                if (j!=0 && j!=5 && pl[i][j-1]!='x' && pl[i][j]=='x' && pl[i][j+1]=='x' && pl[i][j+2]=='x' && pl[i][j+3]=='x' && pl[i][j+4]=='x' && pl[i][j+5]!='x') wynik+=WYGRANA;
//                if (j==0 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]=='o' && pl[i][j+5]!='o') wynik+=PRZEGRANA;
//                if (j==5 && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]=='o' && pl[i][j-1]!='o') wynik+=PRZEGRANA;
//                if (j!=0 && j!=5 && pl[i][j-1]!='o' && pl[i][j]=='o' && pl[i][j+1]=='o' && pl[i][j+2]=='o' && pl[i][j+3]=='o' && pl[i][j+4]=='o' && pl[i][j+5]!='o') wynik+=PRZEGRANA;
//            }
//        }
//    }
//    return wynik;
//}
int ocenaglupsza(char pl[10][10]) {
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 6; j++) {
            if (j < 6) {
                if (j == 0 && pl[i][j] == 'x' && pl[i][j + 1] == 'x' && pl[i][j + 2] == 'x' && pl[i][j + 3] == 'x' &&
                    pl[i][j + 4] == 'x' && pl[i][j + 5] != 'x')
                    return WYGRANA;
                if (j == 5 && pl[i][j] == 'x' && pl[i][j + 1] == 'x' && pl[i][j + 2] == 'x' && pl[i][j + 3] == 'x' &&
                    pl[i][j + 4] == 'x' && pl[i][j - 1] != 'x')
                    return WYGRANA;
                if (j != 0 && j != 5 && pl[i][j - 1] != 'x' && pl[i][j] == 'x' && pl[i][j + 1] == 'x' &&
                    pl[i][j + 2] == 'x' && pl[i][j + 3] == 'x' && pl[i][j + 4] == 'x' && pl[i][j + 5] != 'x')
                    return WYGRANA;
                if (j == 0 && pl[i][j] == 'o' && pl[i][j + 1] == 'o' && pl[i][j + 2] == 'o' && pl[i][j + 3] == 'o' &&
                    pl[i][j + 4] == 'o' && pl[i][j + 5] != 'o')
                    return PRZEGRANA;
                if (j == 5 && pl[i][j] == 'o' && pl[i][j + 1] == 'o' && pl[i][j + 2] == 'o' && pl[i][j + 3] == 'o' &&
                    pl[i][j + 4] == 'o' && pl[i][j - 1] != 'o')
                    return PRZEGRANA;
                if (j != 0 && j != 5 && pl[i][j - 1] != 'o' && pl[i][j] == 'o' && pl[i][j + 1] == 'o' &&
                    pl[i][j + 2] == 'o' && pl[i][j + 3] == 'o' && pl[i][j + 4] == 'o' && pl[i][j + 5] != 'o')
                    return PRZEGRANA;
            }
        }
    }
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 6; j++) {
            if (j < 6) {
                if (j == 0 && pl[i][j] == 'x' && pl[i][j + 1] == 'x' && pl[i][j + 2] == 'x' && pl[i][j + 3] == 'x' &&
                    pl[i][j + 4] == 'x' && pl[i][j + 5] != 'x')
                    return WYGRANA;
                if (j == 5 && pl[i][j] == 'x' && pl[i][j + 1] == 'x' && pl[i][j + 2] == 'x' && pl[i][j + 3] == 'x' &&
                    pl[i][j + 4] == 'x' && pl[i][j - 1] != 'x')
                    return WYGRANA;
                if (j != 0 && j != 5 && pl[i][j - 1] != 'x' && pl[i][j] == 'x' && pl[i][j + 1] == 'x' &&
                    pl[i][j + 2] == 'x' && pl[i][j + 3] == 'x' && pl[i][j + 4] == 'x' && pl[i][j + 5] != 'x')
                    return WYGRANA;
                if (j == 0 && pl[i][j] == 'o' && pl[i][j + 1] == 'o' && pl[i][j + 2] == 'o' && pl[i][j + 3] == 'o' &&
                    pl[i][j + 4] == 'o' && pl[i][j + 5] != 'o')
                    return PRZEGRANA;
                if (j == 5 && pl[i][j] == 'o' && pl[i][j + 1] == 'o' && pl[i][j + 2] == 'o' && pl[i][j + 3] == 'o' &&
                    pl[i][j + 4] == 'o' && pl[i][j - 1] != 'o')
                    return PRZEGRANA;
                if (j != 0 && j != 5 && pl[i][j - 1] != 'o' && pl[i][j] == 'o' && pl[i][j + 1] == 'o' &&
                    pl[i][j + 2] == 'o' && pl[i][j + 3] == 'o' && pl[i][j + 4] == 'o' && pl[i][j + 5] != 'o')
                    return PRZEGRANA;
            }
        }
    }
    return 0;
}

 int ocena(char pl[10][10]){
    int i, j, licznik, wynik;
    int wyst[6] = {0, 0, 0, 0, 0, 0};
    //po rzędach
    for (i=0; i<10; i++){
        licznik=0;
        for (j=0; j<10; j++){
            if (pl[i][j]=='x') licznik++;
            else {wyst[licznik]++; licznik=0;}
            if (j==9) wyst[licznik]++;
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
     for (i=0; i<10; i++){
         licznik=0;
         for (j=0; j<10; j++){
             if (pl[i][j]=='o') licznik++;
             else {wyst[licznik]--; licznik=0;}
             if (j==9) wyst[licznik]--;
         }
     }
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
////    for (i=2; i<6; i++) printf("%d ", wyst[i]);
////    printf("\n");
    //if (wyst[5]>0) return WYGRANA;
    //if (wyst[5]<0) return PRZEGRANA;
    wynik = wyst[2] + wyst[3]*5 + wyst[4]*20; //+ wyst[5]*1000;
    return wynik;
}

int ruchy(char pl[10][10], int glebokosc, int *k, int *m){
    int niepot;
    int wmin = 1000000000;
    int wmax= -1000000000;
    int i, j, war, oc;
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

    while(1) {
        ruchy(pl, 4, k, m);
        printf("Ruch komputera:\n");
        pl[i][j]='x';
        wypisz(pl);

        if (ocena(pl)==WYGRANA) {printf("Komputer wygrał\n"); break;}

        printf("Podaj ruch\n");
        scanf("%d %d", &x, &y);
        pl[x][y] = 'o';
        wypisz(pl);
        if (ocena(pl)==PRZEGRANA) {printf("Wygrałeś!\n"); break;}
    }
}
