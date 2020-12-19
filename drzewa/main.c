#include <stdio.h>
#include <stdlib.h>

struct el_drzewa{
    double w;
    struct el_drzewa *lewy, *prawy;
};

void wstaw(struct el_drzewa **pocz, double war){
    struct el_drzewa *nowy, *ws=*pocz;
    nowy=malloc(sizeof(struct el_drzewa));
    nowy->w = war;
    nowy->lewy = nowy->prawy = 0;
    if (ws==0) *pocz=nowy;
    else{
        while(1){
            if (war < ws->w){
                if (ws->lewy==0) {ws->lewy = nowy; break;}
                else ws=ws->lewy;
            }
            else{
                if (ws->prawy==0) {ws->prawy=nowy; break;}
                else ws=ws->prawy;
            }
        }
    }
}

void wypisz(struct  el_drzewa *pocz){
    if (pocz==0) return;
    wypisz(pocz->lewy);
    printf(" %lf", pocz->w);
    wypisz(pocz->prawy);
}

struct el_drzewa *znajdz(struct  el_drzewa *pocz, double war){
    struct el_drzewa *wynik, *wynik2;
    if (pocz==0) return 0;
    if (pocz->w==war) return pocz;
    wynik=znajdz(pocz->lewy, war);
    if (wynik) return wynik;

    wynik2=znajdz(pocz->prawy, war);
    if (wynik2) return wynik2;
    return 0;
}


int main() {
    struct el_drzewa *d=0, *d2;
    wstaw(&d, 5);
    wstaw(&d, 11);
    wstaw(&d, 4);
    wstaw(&d, 10);
    wstaw(&d, 1);
    wstaw(&d, 8);
    wypisz(d);
    printf("\n");
    d2 = znajdz(d, 5);
    if (d2) d2->w=0;
    wypisz(d);
}
