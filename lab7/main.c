#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOG(text) printf("%s %d %s\n", __FILE__, __LINE__, text)

int **dynamicArray(int i, int j){
    int **array, a;
    array = malloc(sizeof(int *) * i);
    for (a = 0; a < i; a++){
        array[a] = malloc(sizeof(int) * j);
    }
    return array;
}


void freeArray(int **arr, int i){
    int a;
    for (a=0; a<i; a++){
        free(arr[i]);
    }
    free(arr);
}


void printMatrix2x2(int matrix[2][2]){
    printf("%d %d\n", matrix[0][0], matrix[0][1]);
    printf("%d %d\n", matrix[1][0], matrix[1][1]);
}


void sum_matrix2x2(int matrix1[2][2], int matrix2[2][2], int matrix3[2][2]){
    int i,j;

    for (i=0; i<2; i++){
        for (j=0; j<2; j++){
            matrix3[i][j]=matrix1[i][j]+matrix2[i][j];
        }
    }
}


int det(int matrix[2][2]){
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}


void subtract_matrix(int matrix1[2][2], int matrix2[2][2], int matrix3[2][2]){
    int i,j;
    for (i=0; i<2; i++){
        for (j=0; j<2; j++){
            matrix3[i][j]=matrix1[i][j]-matrix2[i][j];
        }
    }
}


char **split(char *text){
    int i=0, counter=0;
    char newstring[20][20];
    char **split_arr;
    while (*text){
        if ((*text)==' '){
            newstring[counter][i]='\0';
            counter++;
            i=0;
        }
        else {
            newstring[counter][i] = *text;
            i++;
        }
        text++;
    }
    newstring[counter][i]='\0';
    counter++;
    newstring[counter][0]=0;
    split_arr = malloc(sizeof(char *) * counter);
    for (i=0; i<counter; i++){
        split_arr[i] = malloc(sizeof(newstring[i]));
        strcpy(split_arr[i], newstring[i]);
    }
    return split_arr;
}


char *unsplit(char **array){
    static char text[50] = "";
    while (*array){
        strcat(text, *array);
        strcat(text, " ");
        array++;
    }
    char *ret;
    ret = text;
    return ret;
}


void print1(char *text){
    printf("( %s )\n", text);
}


void print2(char *text){
    printf("{ %s }\n", text);
}


void print3(char *text){
    printf("[ %s ]\n", text);
}


void print3times(void (*function1)(char *), void (*function2)(char *), void (*function3)(char *), char *text){
    (*function1)(text);
    (*function2)(text);
    (*function3)(text);
}


int cmpfunc(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}


struct fraction{
    int numerator;
    int denominator;
};


struct fraction add(struct fraction fraction1, struct fraction fraction2){
    struct fraction result;
    result.numerator = fraction1.numerator*fraction2.denominator + fraction2.numerator*fraction1.denominator;
    result.denominator = fraction1.denominator * fraction2.denominator;
    return result;
}


struct fraction mulitiply(struct fraction fraction1, struct fraction fraction2){
    struct fraction result;
    result.numerator = fraction1.numerator * fraction2.numerator;
    result.denominator = fraction1.denominator * fraction2.denominator;
    return result;
}


struct Array{
    int dim;
    int *elements;
};


struct Array construct(int size){
    struct Array arr;
    arr.dim = size;
    arr.elements = malloc(sizeof(int) * size);
    return arr;
}



int main() {
    print3times(print1, print2, print3, "siemaneczko");
    int i=system("ls -l");
    printf("%d\n", i);

    FILE *fp;
    char path[1035];
    fp = popen("pwd", "r");
    if (fp==NULL){
        printf("Failed to run command\n");
        exit(1);
    }
    while (fgets(path, sizeof(path), fp) != NULL) printf("%s", path);
    pclose(fp);

    int *item;
    int key=32;
    int values[] = {5, 20, 29, 32, 63};
    item = (int *) bsearch(&key, values, 5, sizeof(int), cmpfunc);
    if (item != NULL) printf("Found item = %d\n", *item);
    else printf("Item = %d could not be found", key);

    printf("Compilation date: %s\n", __DATE__);
    printf("Compilation time: %s\n", __TIME__);
    printf("Current function: %s\n", __FUNCTION__);
    printf("Compilation time: %s\n", __TIME__);
    printf("File name: %s\n", __FILE__);
    printf("Current line: %d\n", __LINE__);

    LOG("hej");

    struct fraction a, b, c, d;
    a.numerator=1;
    a.denominator=2;
    b.numerator=1;
    b.denominator=3;
    c = add(a, b);
    d = mulitiply(a, b);
    printf("%d/%d\n", c.numerator, c.denominator);
    printf("%d/%d\n", d.numerator, d.denominator);
}
