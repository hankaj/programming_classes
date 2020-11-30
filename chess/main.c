#include <stdio.h>
#define PRZEGRANA -1000
#define WYGRANA 1000

//0-król, 1-hetman, 2-wieża, 3-goniec, 4-skoczek, 5-pionek, 6-król_k, 7-hetman_k, 8-wieża_k, 9-goniec_k, 10-skoczek_k, 11-pionek_k, 12-pole puste

void wypisz(int pl[8][8]){
    int i, j;
    for (j=0; j<8; j++){
        for (i=0; i<8; i++){
            if (pl[j][i]<10) printf(" ");
            printf(" %d |", pl[j][i]);
        }

        printf("\n----+----+----+----+----+----+----+----+\n");}
}

void wypisz_ladnie(int pl[8][8]){
    int i, j;
    char symbole[13] = "KHWGSPkhwgsp ";
    for (j=0; j<8; j++){
        for (i=0; i<8; i++){
           printf(" %c |", symbole[pl[j][i]]);
        }

        printf("\n---+---+---+---+---+---+---+---+\n");}
}

//można poprawić, z heurystykami
int ocena(int pl[8][8]){
    int i, j, wynik=0;
    int oc[]={PRZEGRANA,-9,-5,-4,-3,-1,WYGRANA,9,5,4,3,1,0};
    for (i=0;i<8;i++){
        for (j=0;j<8;j++){
            wynik+=oc[pl[i][j]];
        }
    }
    //printf("%d", wynik);
    return wynik;
}

int ilosc_ruchow[]={8,8,4,4,8,3,8,8,4,4,8,3,0};
int dlugosc_ruchu[]={2,8,8,8,2,2,2,8,8,8,2,2,0};

int wekt_y[12][8]={
        {0,1,1,1,0,-1,-1,-1},
        {0,1,1,1,0,-1,-1,-1},
        {0,1,0,-1},
        {1,1,-1,-1},
        {1,2,2,1,-1,-2,-2,-1},
        {-1,0,1},
        {0,1,1,1,0,-1,-1,-1},
        {0,1,1,1,0,-1,-1,-1},
        {0,1,0,-1},
        {1,1,-1,-1},
        {1,2,2,1,-1,-2,-2,-1},
        {-1,0,1}
};

int wekt_x[12][8]={
        {-1,-1,0,1,1,1,0,-1},
        {-1,-1,0,1,1,1,0,-1},
        {-1,0,1,0},
        {-1,1,1,-1},
        {-2,-1,1,2,2,1,-1,-2},
        {-1,-1,-1},
        {-1,-1,0,1,1,1,0,-1},
        {-1,-1,0,1,1,1,0,-1},
        {-1,0,1,0},
        {-1,1,1,-1},
        {-2,-1,1,2,2,1,-1,-2},
        {1,1,1}
};

void przesun_figure(int pl[8][8], int x, int y, int kierunek, int odleglosc){
    int figura, dx, dy;
    figura=pl[x][y];
    dx = odleglosc * wekt_x[figura][kierunek];
    dy = odleglosc * wekt_y[figura][kierunek];
    pl[x+dx][y+dy]=figura;
    pl[x][y]=12; //puste
    if (figura==11 && y+dy==7){
        pl[x+dx][y+dy]=7;
    }
}

void przesun_figure_gracza(int pl[8][8], int z_x, int z_y, int do_x, int do_y){
    int figura;
    figura=pl[z_x][z_y];
    pl[do_x][do_y]=figura;
    pl[z_x][z_y]=12;
    if (figura==5 && do_x==0){
        pl[do_x][do_y]=1;
    }
}

int czy_mozna_tak_postawic(int pl[8][8], int z_x, int z_y, int do_x, int do_y){
    int dx, dy, figura, kierunek, odleglosc, dx_mozliwe, dy_mozliwe, bita_fig;
    dx = do_x - z_x;
    dy = do_y - z_y;
    figura=pl[z_x][z_y];
    // sprawdza, czy jest to figura gracza
    if (figura<=5) {
        // sprawdza możliwe kierunki
        for (kierunek = 0; kierunek < ilosc_ruchow[figura]; kierunek++) {
            // sprawdza różne długości ruchu
            for (odleglosc = 1; odleglosc < dlugosc_ruchu[figura]; odleglosc++) {
                dx_mozliwe = (odleglosc - 1) * wekt_x[figura][kierunek];
                dy_mozliwe = (odleglosc - 1) * wekt_y[figura][kierunek];
                // sprawdza czy po drodze jest niepuste pole
                // sprawdza tylko poprzednią odległość, bo gdyby wszystkie wcześniej nie były puste
                // to już wcześniej zakończyłby tę pętlę
                if (odleglosc >= 2 && pl[z_x + dx_mozliwe][z_y + dy_mozliwe] != 12) break; //12-puste pole
                dx_mozliwe = odleglosc * wekt_x[figura][kierunek];
                dy_mozliwe = odleglosc * wekt_y[figura][kierunek];
                // sprawdza czy ruch nie wykracza poza planszę
                if (z_x + dx_mozliwe >= 0 && z_x + dx_mozliwe < 8 && z_y + dy_mozliwe >= 0 && z_y + dy_mozliwe < 8) {
                    bita_fig = pl[z_x + dx_mozliwe][z_y + dy_mozliwe];
                    // sprawdza czy docelowe pole jest puste czy jest tam figura komputera
                    if (bita_fig == 12 || bita_fig >= 6) {
                        // warunek dla pionka (ruch po skosie z biciem lub ruch do przodu na puste)
                        if (figura != 5 || (bita_fig == 12 && dy_mozliwe == 0) || (bita_fig != 12 && dy_mozliwe != 0)) {
                            // sprawdz czy to mozliwe dx dy jest rowne dx dy
                            if (dx_mozliwe == dx && dy_mozliwe == dy) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int wykonaj_ruch(int pl[8][8], int gl, int *x, int *y, int *k, int *o){
    int px_pom, py_pom, k_pom, o_pom, px, py, dx, dy, kierunek, odleglosc;
    int wynik, wmax, wmin, ruszana_fig, bita_fig, figura;

    wynik=ocena(pl);

    if (gl==0 || 2*wynik>WYGRANA || 2*wynik<PRZEGRANA) return wynik;

    //ruch komputera
    if (gl%2==0){
        // idzie po kolei po rzędach i kolumnach
        for (px=0, wmax=-1000000; px<8; px++){
            for (py=0; py<8; py++){
                figura=pl[px][py];
                // sprawdza, czy jest tam figura komputera
                if (figura>=6 && figura<12){
                    // sprawdza możliwe kierunki
                    for (kierunek=0; kierunek<ilosc_ruchow[figura]; kierunek++){
                        // sprawdza różne długości ruchu
                        for (odleglosc=1; odleglosc<dlugosc_ruchu[figura]; odleglosc++){
                            dx = (odleglosc-1) * wekt_x[figura][kierunek];
                            dy = (odleglosc-1) * wekt_y[figura][kierunek];
                            // sprawdza czy po drodze jest niepuste pole
                            // sprawdza tylko poprzednią odległość, bo gdyby wszystkie wcześniej nie były puste
                            // to już wcześniej zakończyłby tę pętlę
                            if (odleglosc>=2 && pl[px+dx][py+dy]!=12) break; //12-puste pole
                            dx = odleglosc * wekt_x[figura][kierunek];
                            dy = odleglosc * wekt_y[figura][kierunek];
                            // sprawdza czy ruch nie wykracza poza planszę
                            if (px+dx>=0 && px+dx<8 && py+dy>=0 && py+dy<8){
                                bita_fig=pl[px+dx][py+dy];
                                // sprawdza czy docelowe pole jest puste czy jest tam figura przeciwnika
                                if (bita_fig==12 || bita_fig<=5){
                                    // warunek dla pionka (ruch po skosie z biciem lub ruch do przodu na puste)
                                    if (figura !=11 || (bita_fig==12 && dy==0) || (bita_fig!=12 && dy!=0)){
                                        // wykonaj ruch
                                        pl[px+dx][py+dy]=figura;
                                        pl[px][py]=12; //puste
                                        // jeśli pionek doszedł do końca to wymiana na hetmana
                                        if (figura==11 && px+dx==7){
                                            pl[px+dx][py+dy]=7;
                                        }
                                        wynik=wykonaj_ruch(pl, gl-1, &px_pom, &py_pom, &k_pom, &o_pom);
                                        // cofnij ruch
                                        pl[px][py]=figura;
                                        pl[px+dx][py+dy]=bita_fig;
                                        if (wynik>wmax) {wmax=wynik; *x=px; *y=py; *k=kierunek; *o=odleglosc;}
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (wmax>-1000000) return wmax;
        else return 0;
    }


    // ruch przeciwnika
    else{
        // idzie po kolei po rzędach i kolumnach
        for (px=0, wmin=1000000; px<8; px++){
            for (py=0; py<8; py++){
                figura=pl[px][py];
                // sprawdza, czy jest tam figura przeciwnika
                if (figura<=5){
                    // sprawdza możliwe kierunki
                    for (kierunek=0; kierunek<ilosc_ruchow[figura]; kierunek++){
                        // sprawdza różne długości ruchu
                        for (odleglosc=1; odleglosc<dlugosc_ruchu[figura]; odleglosc++){
                            dx = (odleglosc-1) * wekt_x[figura][kierunek];
                            dy = (odleglosc-1) * wekt_y[figura][kierunek];
                            // sprawdza czy po drodze jest niepuste pole
                            // sprawdza tylko poprzednią odległość, bo gdyby wszystkie wcześniej nie były puste
                            // to już wcześniej zakończyłby tę pętlę
                            if (odleglosc>=2 && pl[px+dx][py+dy]!=12) break; //12-puste pole
                            dx = odleglosc * wekt_x[figura][kierunek];
                            dy = odleglosc * wekt_y[figura][kierunek];
                            // sprawdza czy ruch nie wykracza poza planszę
                            if (px+dx>=0 && px+dx<8 && py+dy>=0 && py+dy<8){
                                bita_fig=pl[px+dx][py+dy];
                                // sprawdza czy docelowe pole jest puste czy jest tam figura komputera
                                if (bita_fig==12 || bita_fig>=6){
                                    // warunek dla pionka (ruch po skosie z biciem lub ruch do przodu na puste)
                                    if (figura !=5 || (bita_fig==12 && dy==0) || (bita_fig!=12 && dy!=0)){
                                        // wykonaj ruch
                                        pl[px+dx][py+dy]=figura;
                                        pl[px][py]=12; //puste
                                        // jeśli pionek doszedł do końca to wymiana na hetmana
                                        if (figura==5 && px+dx==0){
                                            pl[px+dx][py+dy]=1;
                                        }
                                        wynik=wykonaj_ruch(pl, gl-1, &px_pom, &py_pom, &k_pom, &o_pom);
                                        // cofnij ruch
                                        pl[px][py]=figura;
                                        pl[px+dx][py+dy]=bita_fig;
                                        if (wynik<wmin) {wmin=wynik; *x=px; *y=py; *k=kierunek; *o=odleglosc;}
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (wmin<1000000) return wmin;
        else return 0;
    }
}

//0-król, 1-hetman, 2-wieża, 3-goniec, 4-skoczek, 5-pionek, 6-król_k, 7-hetman_k, 8-wieża_k, 9-goniec_k, 10-skoczek_k, 11-pionek_k, 12-pole puste

int main() {
    int x1, y1, kierunkek, odleglosc, z_x, z_y, do_x, do_y;
    int *k = &kierunkek;
    int *o = &odleglosc;
    int *x = &x1;
    int *y = &y1;
    int pl[8][8]={{8,10,9,7,6,9,10,8}, {11,11,11,11,11,11,11,11}, {12,12,12,12,12,12,12,12},
                  {12,12,12,12,12,12,12,12}, {12,12,12,12,12,12,12,12}, {12,12,12,12,12,12,12,12},
                  {5,5,5,5,5,5,5,5}, {2,4,3,1,0,3,4,2}};
    while (1){
        printf("Ruch komputera:\n");
        wykonaj_ruch(pl, 4, x, y, k, o);
        przesun_figure(pl, x1,y1,kierunkek,odleglosc);
        wypisz_ladnie(pl);
        if (ocena(pl)*2>WYGRANA) {printf("Komputer wygrał\n"); break;}

        while (1){
        printf("Podaj ruch\n");
        scanf("%d %d %d %d", &z_x, &z_y, &do_x, &do_y);
        if (czy_mozna_tak_postawic(pl, z_x, z_y, do_x, do_y)) break;
        printf("Nie możesz tak postawić\n");
        }

        przesun_figure_gracza(pl, z_x, z_y, do_x, do_y);
        wypisz_ladnie(pl);
        if (ocena(pl)*2<PRZEGRANA) {printf("Wygrałeś\n"); break;}
    }
}
