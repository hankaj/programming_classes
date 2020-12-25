#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <zconf.h>
#define PRZEGRANA -10000
#define WYGRANA 10000

//0-król, 1-hetman, 2-wieża, 3-goniec, 4-skoczek, 5-pionek, 6-król_k, 7-hetman_k, 8-wieża_k, 9-goniec_k, 10-skoczek_k, 11-pionek_k, 12-pole puste

void wypisz_ladnie(int pl[8][8], char mess[200]){
    int i, j;
    char dodaj[10];
    char symbole[13] = "KHWGSPkhwgsp ";
    for (j=0; j<8; j++){
        for (i=0; i<8; i++){
            sprintf(dodaj, " %c |", symbole[pl[j][i]]);
            strcat(mess, dodaj);
        }

        strcat(mess, "\n---+---+---+---+---+---+---+---+\n");}
}


int ocena_z_heurystykami(int pl[8][8]) {
    int i, j, wynik=0;
    static int heurytyki[13][8][8] = {
            // król
            {
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
                    {PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA,PRZEGRANA},
            },
            // hetman
            {
                    {-176, -178, -178, -179, -179, -178, -178, -176},
                    {-178, -180, -180, -180, -180, -180, -180, -178},
                    {-178, -180, -181, -181, -181, -181, -180, -178},
                    {-179, -180, -181, -181, -181, -181, -180, -179},
                    {-180, -180, -181, -181, -181, -181, -180, -179},
                    {-178, -181, -181, -181, -181, -181, -180, -178},
                    {-178, -180, -181, -180, -180, -180, -180, -178},
                    {-176, -178, -178, -179, -179, -178, -178, -176},
            },
            // wieża
            {       {-100, -100, -100, -100, -100, -100, -100, -100},
                    {-101, -102, -102, -102, -102, -102, -102, -101},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-99, -100, -100, -100, -100, -100, -100, -99},
                    {-100, -100, 100, -101, -101, -100, -100, -100},
            },
            // goniec
            {
                    {-56, -58, -58, -58, -58, -58, -58, -56},
                    {-58, -60, -60, -60, -60, -60, -60, -58},
                    {-58, -60, -61, -62, -62, -61, -60, -58},
                    {-58, -61, -61, -62, -62, -61, -61, -58},
                    {-58, -60, -62, -62, -62, -62, -60, -58},
                    {-58, -62, -62, -62, -62, -62, -62, -58},
                    {-58, -61, -60, -60, -60, -60, -61, -58},
                    {-56, -58, -58, -58, -58, -58, -58, -56},
            },
            // skoczek
            {
                    {-50, -52, -54, -54, -54, -54, -52, -50},
                    {-52, -56, -60, -60, -60, -60, -56, -52},
                    {-54, -60, -62, -63, -63, -62, -60, -54},
                    {-54, -61, -63, -64, -64, -63, -61, -54},
                    {-54, -60, -63, -64, -64, -63, -60, -54},
                    {-54, -61, -62, -63, -63, -62, -61, -54},
                    {-52, -56, -60, -61, -61, -60, -56, -52},
                    {-50, -52, -54, -54, -54, -54, -52, -50},
            },
            // pionek
            {
                    {-20, -20, -20, -20, -20, -20, -20, -20},
                    {-30, -30, -30, -30, -30, -30, -30, -30},
                    {-22, -22, -24, -26, -26, -24, -22, -22},
                    {-21, -21, -22, -25, -25, -22, -21, -21},
                    {-20, -20, -20, -24, -24, -20, -20, -20},
                    {-21, -19, -18, -20, -20, -18, -19, -21},
                    {-21, -22, -22, -16, -16, -22, -22, -21},
                    {-20, -20, -20, -20, -20, -20, -20, -20},
            },
            // król komputera
            {
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
                    {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA}
            },
            // hetman komputera
            {
                    {176, 178, 178, 179, 179, 178, 178, 176},
                    {178, 180, 180, 180, 180, 180, 180, 178},
                    {178, 180, 181, 181, 181, 181, 180, 178},
                    {179, 180, 181, 181, 181, 181, 180, 179},
                    {180, 180, 181, 181, 181, 181, 180, 179},
                    {178, 181, 181, 181, 181, 181, 180, 178},
                    {178, 180, 181, 180, 180, 180, 180, 178},
                    {176, 178, 178, 179, 179, 178, 178, 176},
            },
            // wieża komputera
            {       {100, 100, 100, 101, 101, 100, 100, 100},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {99, 100, 100, 100, 100, 100, 100, 99},
                    {101, 102, 102, 102, 102, 102, 102, 101},
                    {100, 100, 100, 100, 100, 100, 100, 100},
            },
            // goniec komputera
            {
                    {56, 58, 58, 58, 58, 58, 58, 56},
                    {58, 61, 60, 60, 60, 60, 61, 58},
                    {58, 62, 62, 62, 62, 62, 62, 58},
                    {58, 60, 62, 62, 62, 62, 60, 58},
                    {58, 61, 61, 62, 62, 61, 61, 58},
                    {58, 60, 61, 62, 62, 61, 60, 58},
                    {58, 60, 60, 60, 60, 60, 60, 58},
                    {56, 58, 58, 58, 58, 58, 58, 56},
            },
            // skoczek komputera
            {
                    {50, 52, 54, 54, 54, 54, 52, 50},
                    {52, 56, 60, 60, 60, 60, 56, 52},
                    {54, 60, 62, 63, 63, 62, 60, 54},
                    {54, 61, 63, 64, 64, 63, 61, 54},
                    {54, 60, 63, 64, 64, 63, 60, 54},
                    {54, 61, 62, 63, 63, 62, 61, 54},
                    {52, 56, 60, 61, 61, 60, 56, 52},
                    {50, 52, 54, 54, 54, 54, 52, 50},
            },
            // pionek komputera
            {
                    {20, 20, 20, 20, 20, 20, 20, 20},
                    {21, 22, 22, 16, 16, 22, 22, 21},
                    {21, 19, 18, 20, 20, 18, 19, 21},
                    {20, 20, 20, 24, 24, 20, 20, 20},
                    {21, 21, 22, 25, 25, 22, 21, 21},
                    {22, 22, 24, 26, 26, 24, 22, 22},
                    {30, 30, 30, 30, 30, 30, 30, 30},
                    {20, 20, 20, 20, 20, 20, 20, 20}
            },
            // puste
            {
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
            }

    };

    for (i=0;i<8;i++){
        for (j=0;j<8;j++){
            wynik+=heurytyki[pl[i][j]][i][j];
        }
    }
    //printf("%d", wynik);
    return wynik;
}


int ilosc_ruchow[]={8,8,4,4,8,3,8,8,4,4,8,3,0};
int dlugosc_ruchu[]={2,8,8,8,2,2,2,8,8,8,2,2,0};

// przesuwanie na boki
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

// przesuwanie góra-dół
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

// przesuwanie figury komputera
void przesun_figure(int pl[8][8], int x, int y, int kierunek, int odleglosc){
    int figura, dx, dy;
    figura=pl[x][y];
    dx = odleglosc * wekt_x[figura][kierunek];
    dy = odleglosc * wekt_y[figura][kierunek];
    pl[x+dx][y+dy]=figura;
    pl[x][y]=12; //puste
    if (figura==11 && x+dx==7){
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
    int wynik, wmax, wmin, bita_fig, figura;

    wynik=ocena_z_heurystykami(pl);

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
                                // sprawdza czy docelowe pole jest puste lub czy jest tam figura przeciwnika
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

int main() {
    int status, gniazdo, dlugosc, nr=0, end=1, gniazdo2, end_conv, gra;
    struct sockaddr_in ser, cli;
    char buf[1000];
    char mess[1000];
    int x1, y1, kierunkek, odleglosc, z_x, z_y, do_x, do_y;
    int *k = &kierunkek;
    int *o = &odleglosc;
    int *x = &x1;
    int *y = &y1;

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo==-1) {printf("blad socketn"); return 0;}

    ser.sin_family = AF_INET;
    ser.sin_port = htons(9000);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof(ser));
    if (status==-1) {printf("blad bind\n"); return 0;}

    status = listen(gniazdo, 10);
    if (status==-1) {printf("blad listen\n"); return 0;}

    while (end){
        end_conv=1;
        dlugosc=sizeof(cli);
        gniazdo2=accept(gniazdo, (struct sockaddr*)&cli, (socklen_t *)&dlugosc);
        if (gniazdo2==-1) {printf("blad accept"); return 0;}
        while (end_conv){
            int pl[8][8]={{8,10,9,7,6,9,10,8}, {11,11,11,11,11,11,11,11}, {12,12,12,12,12,12,12,12},
                      {12,12,12,12,12,12,12,12}, {12,12,12,12,12,12,12,12}, {12,12,12,12,12,12,12,12},
                      {5,5,5,5,5,5,5,5}, {2,4,3,1,0,3,4,2}};
            gra=0;
            memset(buf,0,strlen(buf));
            memset(mess,0,strlen(mess));
            status=recv(gniazdo2,buf,sizeof(buf)-1,0);
            buf[status]='\0';
            printf("Otrzymałem: %s\n",buf);
            if (buf[0]=='Q') {sprintf(mess, "Zgoda, serwer konczy prace\n"); end=0; end_conv=0;}
            else if (buf[0]=='N') sprintf(mess, "Jestes klientem nr %d\n",nr++);
            else if (buf[0]=='P') {sprintf(mess, "Kończę rozmowę\n"); end_conv=0;}
            else if (buf[0]=='G') gra=1;
            else sprintf(mess, "Nie rozumiem pytania\n");

            while (gra){
                memset(buf,0,strlen(buf));
                memset(mess,0,strlen(mess));
                wykonaj_ruch(pl, 4, x, y, k, o);
                przesun_figure(pl, x1,y1,kierunkek,odleglosc);
                wypisz_ladnie(pl, mess);
                if (ocena_z_heurystykami(pl)*2>WYGRANA) {sprintf(mess,"Komputer wygrał.\n"); gra=0; break;}
                if (ocena_z_heurystykami(pl)*2<PRZEGRANA) {sprintf(mess, "Wygrałeś.\n"); gra=0; break;}
                status=send(gniazdo2,mess,strlen(mess),0);
                fflush(stdout);

                status=recv(gniazdo2,buf,sizeof(buf)-1,0);
                buf[status]='\0';
                printf("Otrzymałem: %s\n",buf);
                sscanf(buf, "%d %d %d %d", &z_x, &z_y, &do_x, &do_y);
                przesun_figure_gracza(pl, z_x, z_y, do_x, do_y);
                if (ocena_z_heurystykami(pl)*2<PRZEGRANA) {sprintf(mess,"Wygrałeś.\n");gra=0; break;}
                if (ocena_z_heurystykami(pl)*2>WYGRANA) {sprintf(mess,"Komputer wygrał.\n");gra=0; break;}

            }

            status=send(gniazdo2,mess,strlen(mess),0);
            fflush(stdout);
        }
        close(gniazdo2);
    }

    close(gniazdo);
}

