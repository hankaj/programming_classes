#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *ptr1, int *ptr2){
    int temp;
    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}


void swapText(char *arr1, char *arr2){
    while (*arr1 && *arr2){
        char temp;
        temp = *arr1;
        *arr1 = *arr2;
        *arr2 = temp;
        arr1++; arr2++;
    }
}


void rotate(int *a, int *b, int *c){
    int temp_b, temp_c;
    temp_b = *b;
    *b = *a;
    temp_c = *c;
    *c = temp_b;
    *a = temp_c;
}


int accumulate(int *begin, int *end){
    int sum=0;
    while (begin!=end){
        sum += *begin;
        begin++;
    }
    return sum;
}


int distance(int *begin, int *end){
    int num_elements=0;
    while (begin!=end){
        num_elements++;
        begin++;
    }
    return num_elements;
}


int comparator(const void * p1, const void * p2){
    return (*(int*)p1 - *(int*)p2);
}


int word_comparator(const void * p1, const void * p2) {
    return strcmp(*(const char**)p1, *(const char**)p2);
}


void sort(int *arr, int size){
    qsort(arr, size, sizeof(int), comparator);
}


void sort2(int *begin, int *end){
    int size = distance(begin, end);
    qsort(begin, size, sizeof(int), comparator);
}


void sort3(const char* arr[], int size){
    qsort(arr, size, sizeof(const char*), word_comparator);
}


struct Wynik{
    char nazwisko[50];
    int glosy;
};


void increase(void *num){
    (*(int *)num)++;
}


void wiarolomnySystemDemokratyczny(struct Wynik wyniki[], int len){
    int i;
    for (i=0; i<len; i++){
        if (strcmp(wyniki[i].nazwisko,"Nowak")==0){
            wyniki[i].glosy-=10;
        }
        printf("%s %d\n", wyniki[i].nazwisko, wyniki[i].glosy);
    }
}


int vote_comparator(const void * p1, const void * p2){
    int num_votes1 = (*(struct Wynik*)p1).glosy;
    int num_votes2 = (*(struct Wynik*)p2).glosy;
    return num_votes1 - num_votes2;
}


void sortujWynikiWyborcze(struct Wynik wyniki[], int size){
    qsort(wyniki, size, sizeof(struct Wynik), vote_comparator);
}


struct employee{
    char *name;
    char *surname;
    int age;
};


struct employee *findEmployee(struct employee employees[], int len, char *surname){
    int i=0;
    while (i < len){
        if (strcmp(employees[i].surname, surname)==0) return &employees[i];
        i++;
    }
    return NULL;
}


enum plec {KOBIETA, MEZCZYZNA};


struct osoba{
    enum plec plec_osoby;
    char *imie;
};


void losujObiadSmoka(struct osoba osoby[], int len){
    int i;
    while (len){
        enum plec wylosowa_plec = rand()%2;
        for (i=0; i<len; i++){
            if (osoby[i].plec_osoby==wylosowa_plec){
                printf("Imię osoby zjedzonej przez smoka: %s\n", osoby[i].imie);
                osoby[i].plec_osoby=osoby[len-1].plec_osoby;
                osoby[i].imie = osoby[len-1].imie;
                len--;
                break;
            }
        }
    }
}


int main() {
    struct osoba osoba1, osoba2, osoba3, osoba4;
    osoba1.plec_osoby=KOBIETA;
    osoba1.imie="Hania";
    osoba2.plec_osoby=KOBIETA;
    osoba2.imie="Monika";
    osoba3.plec_osoby=MEZCZYZNA;
    osoba3.imie="Marcin";
    osoba4.plec_osoby=MEZCZYZNA;
    osoba4.imie="Michał";
    struct osoba osoby[] = {osoba1, osoba2, osoba3, osoba4};
    losujObiadSmoka(osoby, sizeof(osoby)/sizeof(struct osoba));
    return 0;
}
