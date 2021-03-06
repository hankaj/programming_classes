#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <zconf.h>

int main() {
    int status, gniazdo, dlugosc, nr=0, end=1, gniazdo2, end_conv=1;
    struct sockaddr_in ser, cli;
    char buf[200];
    char mess[200];

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo==-1) {printf("blad socketn"); return 0;}

    ser.sin_family = AF_INET;
    ser.sin_port = htons(9000);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof(ser));
    if (status==-1) {printf("blad bind\n"); return 0;}

    status = listen(gniazdo, 10);
    if (status==-1) {printf("blad listen\n"); return 0;}

//    while (end){
//        dlugosc=sizeof(cli);
//        gniazdo2=accept(gniazdo, (struct sockaddr*)&cli, (socklen_t *)&dlugosc);
//        if (gniazdo2==-1) {printf("blad accept"); return 0;}
//        recv(gniazdo2,buf,sizeof(buf),0);
//        printf("Otrzymałem: %s\n",buf);
//        fflush(stdout);
//        if (buf[0]=='Q') {sprintf(buf, "Zgoda, serwer konczy prace"); end=0;}
//        else if (buf[0]=='N') sprintf(buf, "Jestes klientem nr %d",nr++);
//        else sprintf(buf, "Nie rozumiem pytania");
//        send(gniazdo2,buf,strlen(buf),0);
//        fflush(stdout);
//        close(gniazdo2);
//    }

    while (end){
        end_conv=1;
        dlugosc=sizeof(cli);
        gniazdo2=accept(gniazdo, (struct sockaddr*)&cli, (socklen_t *)&dlugosc);
        if (gniazdo2==-1) {printf("blad accept"); return 0;}
        while (end_conv){
            strcpy(buf, "");
            strcpy(mess, "");
            //printf("buf1: %s koniec buff1", buf);
            status=recv(gniazdo2,buf,sizeof(buf)-1,0);
            buf[status]='\0';
            //printf("buf: %s koniec buf\n", buf);
            printf("Otrzymałem: %s\n",buf);
            if (buf[0]=='Q') {sprintf(mess, "Zgoda, serwer konczy prace\n"); end=0; end_conv=0;}
            else if (buf[0]=='N') sprintf(mess, "Jestes klientem nr %d\n",nr++);
            else if (buf[0]=='P') {sprintf(mess, "Kończę rozmowę\n"); end_conv=0;}
            else sprintf(mess, "Nie rozumiem pytania\n");
            status=send(gniazdo2,mess,strlen(mess),0);
            fflush(stdout);
        }
        close(gniazdo2);
    }

    close(gniazdo);
}
