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



int main() {
    const char* arr[] = {"hani","duap","hcar","lody","kisi"};
    int i;

    sort3(arr, 5);

    for (i=0; i<5; i++) printf("%s ", arr[i]);
    return 0;
}
