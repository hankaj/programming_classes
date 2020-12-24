#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <zconf.h>

int main() {
    FILE *plik;
    int w2;
    int status, gniazdo, dlugosc, nr=0, end=1, gniazdo2, end_conv;
    struct sockaddr_in ser, cli;
    char nazwa_pliku[200];
    char buf[200];
    char mess[200];
    char tu_wczytaj[200];
    long dlugosc_pliku;

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
            memset(buf,0,strlen(buf));
            memset(mess,0,strlen(mess));
            status=recv(gniazdo2,buf,sizeof(buf)-1,0);
            buf[status-1]='\0';
            printf("Otrzymałem: %s\n",buf);
            if (buf[0]=='Q') {sprintf(mess, "Zgoda, serwer konczy prace\n"); end=0; end_conv=0;}
            else if (buf[0]=='N') sprintf(mess, "Jestes klientem nr %d\n",nr++);
            else if (buf[0]=='P') {sprintf(mess, "Kończę rozmowę\n"); end_conv=0;}
            else {
                strcpy(nazwa_pliku, buf);
                plik = fopen(buf, "r");
                if (plik){
//                    w2 = fscanf(plik, "%s", &tu_wczytaj);
//                    if (w2) sprintf(mess, "%s", tu_wczytaj);
//                    else sprintf(mess, "Nie udało się odczytać pliku\n");
//                    fclose(plik);
//                    w2=fscanf(plik, "%s", &tu_wczytaj);
//                    if (w2){
//                        while (tu_wczytaj[0]) {
//                            strcat(mess, tu_wczytaj);
//                            w2=fscanf(plik, "%s", &tu_wczytaj);
//                        }
//                    }
//                    else sprintf(mess, "Nie udało się odczytać pliku\n");
//                    fclose(plik);
                    fseek(plik, 0, SEEK_END);
                    dlugosc_pliku = ftell(plik);
                    fseek(plik, 0, SEEK_SET);
                    fread(mess, 1, dlugosc_pliku, plik);
                    mess[dlugosc_pliku]='\0';
                    fclose(plik);
                }
                else {
                    sprintf(mess, "Nie udało się otworzyć pliku\n");
                }
            }
            status=send(gniazdo2,mess,strlen(mess),0);
            fflush(stdout);
        }
        close(gniazdo2);
    }

    close(gniazdo);
}
