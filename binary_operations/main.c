#include <stdio.h>
#include <stdbool.h>
#include <math.h>


void printBinary(long long number){
    int i, binary_number[10];
    for (i=0; number>0; i++){
        binary_number[i] = number%2;
        number/=2;
    }
    // print number in right order
    for (i=i-1; i>=0; i--){
        printf("%d", binary_number[i]);
    }
    printf("\n");
}


bool isEnabled(long long number, unsigned bit){
    return (number & (1 << bit));
}


long long enableBit(long long number, unsigned bit2Enable){
    return number | (1 << bit2Enable);
}


long long disableBit(long long number, unsigned bit2Disable){
    return number & ~(1 << bit2Disable);
}


long long disableEvenBits(long long number){
    int length = floor(log2(number)) + 1;
    int i;
    for (i=0; i<=length; i+=2){
        number=disableBit(number, i);
    }
    return number;
}


unsigned char getByte(long long number, unsigned byte){
    return ((number >> (8 * byte)) & 0xff);
}


long long changeBytesOrder(long long number){
    long long new_number=0;
    int i;
    int length = floor(log2(number) / 8) + 1;
    for (i=0; i<length; i++){
        new_number += (getByte(number, i) << ((length-i-1)*8));
    }
    return new_number;
}


bool getArrayBit(int array[], unsigned element, unsigned bit){
    return (array[element] >> bit) & 1;
}


long long multiplyBy10(long long number){
    return (number << 3) + (number << 1);
}



int main() {
    int array[]={1, 2, 3, 4};
    printBinary(66);
    printf("%d\n", isEnabled(13, 1));
    printf("%lld\n", enableBit(13, 1));
    printf("%lld\n", disableBit(15, 1));
    printf("%02x\n", getByte(287454020, 3));
    printf("%d\n", getArrayBit(array, 3, 0));
    printf("%d\n", disableEvenBits(66));
    printf("%d\n", multiplyBy10(12));
    printf("%lld\n", changeBytesOrder(287454020));
}
