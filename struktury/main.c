#include <stdio.h>
#include <stdlib.h>

struct el_listy{
    double w;
    struct el_listy *nast;
};

void dopisz(struct el_listy **pocz, double war){
    struct el_listy *nowy, *ostatni=*pocz;
    nowy=malloc(sizeof(struct el_listy));
    nowy->w=war;
    nowy->nast=0;
    if (ostatni==0) *pocz=nowy;
    else {
        while (ostatni->nast) ostatni=ostatni->nast;
        ostatni->nast=nowy;
    }
}

void wypisz(struct  el_listy *pocz){
    while (pocz) {printf("%lf\n",pocz->w); pocz=pocz->nast;}
}

void wstaw(struct  el_listy **pocz, double war){
    struct el_listy *nowy, *ww=*pocz;
    nowy=malloc(sizeof(struct el_listy));
    nowy->w=war;
    if (ww==0 || war < ww->w) {nowy->nast = ww; *pocz=nowy;} // nie może być na odwrót, bo gdy ww=0 to nie da się ww->w
    else{
        // przesuwamy się aż dojdziemy do ostatniego elementu albo wartość następnego elementu będzie większa od war
        // nie może być na odwrót też
        while (ww->nast!=0 && war > ww->nast->w) ww = ww->nast;
        nowy->nast = ww->nast;
        ww->nast = nowy;
    }
}

void usun(struct el_listy **pocz, double war){
    struct el_listy *pom, *ww=*pocz;
    if (ww==0) return;
    if (war == ww->w) {*pocz=ww->nast; free(ww);}
    else{
        while (ww->nast!=0 && war != ww->nast->w) ww = ww->nast;
        if (ww->nast!=0 && war == ww->nast->w){
            pom=ww->nast;
            ww->nast = ww->nast->nast;
            free(pom);
        }
    }
}


struct el_listy *znajdz(struct  el_listy *pocz, double war){
    while (pocz && pocz->w != war /* && pocz->nast*/) pocz=pocz->nast;
    //if (pocz==0) return 0;
    if (pocz==0 || pocz->w==war) return pocz;
    return 0;
}

struct el_listy *kopiuj_liste(struct  el_listy *pocz){
    struct el_listy *nowy, *poprzedni, *lista2=0, *ww=pocz;
    while (pocz){
        nowy=malloc(sizeof(struct el_listy));
        nowy->w = pocz->w;
        if (lista2==0) lista2=nowy;
        else poprzedni->nast=nowy;
        poprzedni=nowy;
        pocz=pocz->nast;
    }
    if (lista2) nowy->nast=0;
    return lista2;
}

struct el_listy *dodaj_listy(struct el_listy *pocz1, struct el_listy *pocz2){
    struct el_listy *kop1, *kop2, *pom;
    kop1 = kopiuj_liste(pocz1);
    kop2 = kopiuj_liste(pocz2);
    if (kop1==0) return kop2;
    pom = kop1;
    while (pom->nast) pom = pom->nast;
    pom->nast=kop2;
    return kop1;
}

int main() {
    struct el_listy *w2, *w3, *ws=0, *w4=0;
    // czy działa dopisz i wypisz
    ws=malloc(sizeof(struct el_listy));
    ws->w=2;
    ws->nast=0;
    dopisz(&ws, 5);
    dopisz(&ws,10);
    //wypisz(ws);
    // czy działa wstaw
    wstaw(&ws, 8);
    wypisz(ws);
    printf("\n");
    // czy działa usuń
    usun(&ws, 10);
    wypisz(ws);
    printf("\n");
    // czy działa znajdź
    w2 = znajdz(ws, 5);
    if (w2) w2->w=6;
    wypisz(ws);
    printf("\n");
    // czy działa kopiuj
    w2=kopiuj_liste(ws);
    wstaw(&w2, 7);
    wypisz(w2);
    printf("dodaj\n");

    // czy działa dodaj
    w3=dodaj_listy(ws, w2);
    wypisz(w3);
}
