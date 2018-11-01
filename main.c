#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "caesarinfo.h"
#include "caesarss.c"

int main()

{
    int answer;
    int shift;
    char cipher[50];

    printf("Please enter the text. ");
    gets(cipher);

    printf("How many shifts? ");
    scanf("%d", &shift);
    shift = abs(shift);

    printf("Do you want to encrypt or decrypt the text? Type 0 to encrypt or 1 to decrypt. ");
    scanf("%d", &answer);


    if(answer == 0){

        encrypt(cipher, shift);

    }

    if(answer == 1){

        decrypt(cipher, shift);

    }


    return 0;
}
