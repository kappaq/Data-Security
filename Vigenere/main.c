#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Vsource.c"
#include "Vheader.h"


int main()
{

    int answer;
    char cipher[256], keyword[33];

    printf("Please enter the text. ");
    scanf("%s", &cipher);

    printf("What's the keyword? ");
    scanf("%s", &keyword);

    printf("Do you want to encrypt or decrypt the text? Type 0 to encrypt or 1 to decrypt. ");
    scanf("%d", &answer);

    if(answer == 0){

        encrypt(cipher, keyword);

    }

    if(answer == 1){

        decrypt(cipher, keyword);

    }

    return 0;

}
