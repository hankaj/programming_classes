#include <stdio.h>

int main() {
    FILE *wsk, *plik1, *plik2;
    int w, w2, w3, i, zm1;

    wsk = fopen("plik1.txt", "w");
    if (wsk==0) printf("Błąd otwarcia.\n");
    else {
        for (i=1; i<=1000; i++){
            w = fprintf(wsk, "%d\n", i);
        }
        fclose(wsk);
    }

    plik1 = fopen("plik1.txt", "r");
    plik2 = fopen("plik2.txt", "w");
    if (plik1 && plik2) {
        for (i = 1; i <= 1000; i++) {
            w2 = fscanf(plik1, "%d", &zm1);
            if (i % 2 == 0) {
                w3 = fprintf(plik2, "%d\n", zm1);
            }
        }

        fclose(plik1);
        fclose(plik2);
    }
    else printf("Błąd otwarcia.\n");

}
