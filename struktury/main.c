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
    if (ostatni==0) *pocz=nowy; // jeśli lista jest pusta to wstawiamy do niej element nowy
    else {
        while (ostatni->nast) ostatni=ostatni->nast; // przesuwamy się aż ostatni->nast=0
        ostatni->nast=nowy;
    }
}


void wypisz(struct el_listy *pocz){
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
        // nowy element wstawiamy między ten na który wskazuje ww a następny
        nowy->nast = ww->nast;
        ww->nast = nowy;
    }
}


void usun(struct el_listy **pocz, double war){
    struct el_listy *pom, *ww=*pocz;
    if (ww==0) return; // pusta lista, nie da się nic usunać
    if (war == ww->w) {*pocz=ww->nast; free(ww);}
    else{
        while (ww->nast!=0 && war != ww->nast->w) ww = ww->nast;
        if (ww->nast!=0 && war == ww->nast->w){
            pom=ww->nast; // potrzebujemy pom, żeby wiedzieć potem które miejsce zwolnić
            ww->nast = ww->nast->nast;
            free(pom);
        }
    }
}


struct el_listy *znajdz(struct  el_listy *pocz, double war){
    while (pocz && pocz->w != war /* && pocz->nast*/) pocz=pocz->nast;
    return pocz;
    //if (pocz==0) return 0;
//    if (pocz==0 || pocz->w==war) return pocz;
//    return 0;
}


struct el_listy *kopiuj_liste(struct  el_listy *pocz){
    struct el_listy *nowy, *poprzedni, *lista2=0;
    // jeśli pocz=0 to zwracam listę2=0
    while (pocz){
        // tworzę nowy element
        nowy=malloc(sizeof(struct el_listy));
        // przypisuję mu wartość elementu na który wskazuje pocz
        nowy->w = pocz->w;
        // jeśli lista2 nie ma żadnych elementów, to pierwszym elementem będzie nowy
        if (lista2==0) lista2=nowy;
        // jeśli ma, to łączę poprzedni element z nowy
        else poprzedni->nast=nowy;
        // nowy element jest już elementem poprzednim potrzebnym w następnej iteracji pętli
        poprzedni=nowy;
        // przesuwam się po liście1 (nie ma następnej iteracji pętli, gdy element jest ostatni
        pocz=pocz->nast;
    }
    // "zamykam" listę2, jeśli nie jest zerowa
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


void zwolnij_liste(struct el_listy *pocz){
    struct el_listy *pom, *ww=pocz;

    while (ww){
        pom=ww;
        ww = ww->nast;
        free(pom);
    }
}


int main() {
    struct el_listy *w2, *w3, *ws=0, *w4=0;
    // czy działa dopisz i wypisz
    ws=malloc(sizeof(struct el_listy));
    ws->w=2;
    ws->nast=0;
    printf("dopisz:\n");
    dopisz(&ws, 5);
    dopisz(&ws,10);
    wypisz(ws);

    // czy działa wstaw
    printf("\nwstaw:\n");
    wstaw(&ws, 8);
    wypisz(ws);

    // czy działa usuń
    printf("\nusuń:\n");
    usun(&ws, 10);
    wypisz(ws);

    // czy działa znajdź
    printf("\nznajdź:\n");
    w2 = znajdz(ws, 5);
    if (w2) w2->w=6;
    wypisz(ws);

    // czy działa kopiuj
    printf("\nkopiuj:\n");
    w2=kopiuj_liste(ws);
    wstaw(&w2, 7);
    wypisz(w2);

    // czy działa dodaj
    printf("\ndodaj:\n");
    w3=dodaj_listy(ws, w2);
    wypisz(w3);

    // czy działa zwolnij;
    zwolnij_liste(ws);
}
