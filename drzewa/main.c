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
    printf("%lf d", pocz->w);
    wypisz(pocz->prawy);
}


struct el_drzewa *znajdz(struct  el_drzewa *pocz, double war){
    struct el_drzewa *wynik, *wynik2;
    if (pocz==0) return 0;
    if (pocz->w==war) return pocz;
    wynik=znajdz(pocz->lewy, war);
    if (wynik) return wynik;

    wynik2=znajdz(pocz->prawy, war);
    return wynik2;
}


int max_wysokosc(struct el_drzewa *pocz){
    int wynik1, wynik2;
    if (pocz==0) return 0;
    wynik1=1+max_wysokosc(pocz->lewy);
    wynik2=1+max_wysokosc(pocz->prawy);
    if (wynik1>wynik2) return wynik1;
    else return wynik2;
}


int min_wysokosc(struct el_drzewa *pocz){
    int wynik1, wynik2;
    if (pocz==0) return 0;
    wynik1=1+min_wysokosc(pocz->lewy);
    wynik2=1+min_wysokosc(pocz->prawy);
    if (wynik1<wynik2) return wynik1;
    else return wynik2;
}


void przesun(struct  el_drzewa *pocz, struct el_drzewa **koniec, int wysokosc){
    if (pocz->lewy==0) {*koniec=pocz; return;}
    if (pocz->prawy==0) {*koniec=pocz; return;}
    if (wysokosc){
        przesun(pocz->lewy, koniec, wysokosc-1);
        przesun(pocz->prawy, koniec, wysokosc-1);
    }
}


void dopisz(struct el_drzewa *pocz, double war){
    struct el_drzewa *nowy, *koniec=0;
    int wysokosc;

    nowy=malloc(sizeof(struct el_drzewa));
    nowy->w = war;
    nowy->lewy = nowy->prawy = 0;

    wysokosc = min_wysokosc(pocz);
    przesun(pocz, &koniec,wysokosc-1);
    if (koniec->lewy==0) koniec->lewy=nowy;
    else koniec->prawy=nowy;
}


int main() {
    struct el_drzewa *d=0, *d2;
    wstaw(&d, 4);
    wstaw(&d, 8);
    wstaw(&d, 2);
    wstaw(&d, 12);
    wstaw(&d, 10);
    wstaw(&d, 5);
    wstaw(&d, 1);

    wypisz(d);
    printf("\n");
    d2 = znajdz(d, 5);
    if (d2) d2->w=0;
    wypisz(d);
}
