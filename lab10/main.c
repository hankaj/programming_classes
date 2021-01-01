#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct pierwiastki{
    int ilosc_pierwiastkow;
    double x1;
    double x2;
};

struct pierwiastki podaj_pierwiastki(double a, double b, double c){
    struct pierwiastki odpowiedz;
    double delta;
    delta = b*b - 4*a*c;
    if (delta<0) {odpowiedz.ilosc_pierwiastkow=0; return odpowiedz;}
    if (delta==0) {odpowiedz.ilosc_pierwiastkow=1; odpowiedz.x1=(-b/(2*a)); return odpowiedz;}
    odpowiedz.ilosc_pierwiastkow=2;
    odpowiedz.x1 = (-b - sqrt(delta))/(2*a);
    odpowiedz.x2 = (-b + sqrt(delta))/(2*a);
    return odpowiedz;
}

//------------------------------------------------------------------------------------------------------

struct WiadomoscDoWyborcowX{
    char tresc[20];
    int stopien_waznosci;
};

struct WiadomoscDoWyborcowY{
    char tresc[20];
    int stopien_waznosci;
};

struct WiadomoscDoWyborcowZ{
    char tresc[20];
    int stopien_waznosci;
};

enum WiadomosciDoWyborcow {WIADOMOSC_DO_WYBORCOW_X, WIADOMOSC_DO_WYBORCOW_Y, WIADOMOSC_DO_WYBORCOW_Z};

struct WiadomoscDoWyborcow{
    enum WiadomosciDoWyborcow typ_wiadomosci;
    union dostepne_wiadomosci{
        struct WiadomoscDoWyborcowX wiadomoscX;
        struct WiadomoscDoWyborcowY wiadomoscY;
        struct WiadomoscDoWyborcowZ wiadomoscZ;
    } wiadomosc;
};

void przekazWiadomoscWyborcomX(struct WiadomoscDoWyborcow przekazywana_wiadomosc){
    if (przekazywana_wiadomosc.typ_wiadomosci==WIADOMOSC_DO_WYBORCOW_Y) printf("kosmopolici\n");
    else if (przekazywana_wiadomosc.typ_wiadomosci==WIADOMOSC_DO_WYBORCOW_Z) printf("volksdeutsche\n");
    else printf("%s\n", przekazywana_wiadomosc.wiadomosc.wiadomoscX.tresc);
}

void przekazWiadomoscWyborcomY(struct WiadomoscDoWyborcow przekazywana_wiadomosc){
    if (przekazywana_wiadomosc.typ_wiadomosci==WIADOMOSC_DO_WYBORCOW_X) printf("nacjonaliści\n");
    else if (przekazywana_wiadomosc.typ_wiadomosci==WIADOMOSC_DO_WYBORCOW_Z) printf("volksdeutsche\n");
    else printf("%s\n", przekazywana_wiadomosc.wiadomosc.wiadomoscY.tresc);
}

void przekazWiadomoscWyborcomZ(struct WiadomoscDoWyborcow przekazywana_wiadomosc){
    if (przekazywana_wiadomosc.typ_wiadomosci==WIADOMOSC_DO_WYBORCOW_X) printf("nacjonaliści\n");
    else if (przekazywana_wiadomosc.typ_wiadomosci==WIADOMOSC_DO_WYBORCOW_Y) printf("kosmopolici\n");
    else printf("%s\n", przekazywana_wiadomosc.wiadomosc.wiadomoscZ.tresc);
}

//------------------------------------------------------------------------------------------------------

struct TorbaCukierkow{
    int licznik;
};

void poczestunek(){
    srand(time(NULL));
    int prawdopodobienstwo;
    int liczba_uczniow = rand() % 50;
    int uczniowie_poczestowani=0;
    struct TorbaCukierkow torba;
    torba.licznik = liczba_uczniow-(liczba_uczniow%10)+10;

    while (torba.licznik && uczniowie_poczestowani<liczba_uczniow){
        prawdopodobienstwo=rand() % 5;
        if (prawdopodobienstwo==0) torba.licznik-=2;
        else torba.licznik--;
        uczniowie_poczestowani++;
    }

    printf("liczba osób, które dostało cukierki: %d\n", uczniowie_poczestowani);
    printf("liczba osób, które nie dostało cukierkow: %d\n", liczba_uczniow-uczniowie_poczestowani);
}


int main() {
    printf("%d\n", podaj_pierwiastki(1, 7, 12).ilosc_pierwiastkow);
    printf("%lf\n", podaj_pierwiastki(1, 7, 12).x1);
    printf("%lf\n", podaj_pierwiastki(1, 7, 12).x2);
    printf("\n");

    struct WiadomoscDoWyborcow wybrana_wiadomosc;
    wybrana_wiadomosc.typ_wiadomosci=WIADOMOSC_DO_WYBORCOW_X;
    strcpy(wybrana_wiadomosc.wiadomosc.wiadomoscX.tresc, "wygralismy!!!");

    przekazWiadomoscWyborcomX(wybrana_wiadomosc);
    przekazWiadomoscWyborcomY(wybrana_wiadomosc);
    przekazWiadomoscWyborcomZ(wybrana_wiadomosc);
    printf("\n");

    poczestunek();
}
