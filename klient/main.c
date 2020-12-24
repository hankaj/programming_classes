#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <zconf.h>

int status,gniazdo;
struct sockaddr_in ser;
int end=1;
char buf[200];
char mess[200];

int main() {
    gniazdo = socket(AF_INET,SOCK_STREAM,0);
    if (gniazdo==-1) {printf("blad socket\n"); return 0;}

    ser.sin_family = AF_INET;
    ser.sin_port = htons(9000);
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");

//    printf("Podaj tekst:\n");
//    fgets(buf,sizeof(buf), stdin);

    status = connect(gniazdo, (struct sockaddr*)&ser, sizeof(ser));
    printf("status: %d\n", status);
    if (status<0) {printf("blad connect\n"); return 0;}

//    status = send(gniazdo, buf, strlen(buf),0);
//    fflush(stdout);
//    status = recv(gniazdo, buf, sizeof(buf)-1,0);
//    fflush(stdout);
//    buf[status]='\0';
//    printf("Otrzymałem: %s\n",buf);

    while (end) {
        strcpy(buf, "");
        strcpy(mess, "");
        printf("Podaj tekst:\n");
        fgets(mess,sizeof(mess), stdin);
        //printf("mess: %s\n koniec mess", mess);
        status = send(gniazdo, mess, strlen(mess),0);
        fflush(stdout);
        if (mess[0]=='P' || mess[0]=='Q') end=0;
        status = recv(gniazdo, buf, sizeof(buf)-1,0);
        //fflush(stdout);
        buf[status]='\0';
        printf("Otrzymałem: %s\n",buf);
    }

    close(gniazdo);
}
