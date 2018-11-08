#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Vheader.h"

void encrypt(char cipher[], char keyword[]){

    int i, j;
    int cipherlen = strlen(cipher);
    int keywordlen = strlen(keyword);
    char encryptedcipher[cipherlen], decryptedcipher[cipherlen];
    char newkeyword[cipherlen];

    for(i = 0, j = 0; i < cipherlen; ++i, ++j){
        if(j == keywordlen)
            j = 0;

        newkeyword[i] = keyword[j];
    }

    newkeyword[i] = '\0';

    for(i = 0, j = 0; i < cipherlen; ++i, ++j){
        if(j == keywordlen)
            j = 0;

        newkeyword[i] = keyword[j];
    }

    newkeyword[i] = '\0';


    for(i = 0; i < cipherlen; ++i)
        encryptedcipher[i] = ((cipher[i] + newkeyword[i]) % 26) + 'A';

    encryptedcipher[i] = '\0';

    printf("Original Message: %s", cipher);
    printf("\nKey: %s", keyword);
    printf("\nNew Generated Key: %s", newkeyword);
    printf("\nEncrypted Message: %s", encryptedcipher);

}

void decrypt(char cipher[], char keyword[]){

    int i, j;
    int cipherlen = strlen(cipher);
    int keywordlen = strlen(keyword);
    char encryptedcipher[cipherlen], decryptedcipher[cipherlen];
    char newkeyword[cipherlen];

    for(i = 0, j = 0; i < cipherlen; ++i, ++j){
        if(j == keywordlen)
            j = 0;

        newkeyword[i] = keyword[j];
    }

    newkeyword[i] = '\0';

    for(i = 0; i < cipherlen; ++i)
        decryptedcipher[i] = (((cipher[i] - newkeyword[i]) + 26) % 26) + 'A';

    decryptedcipher[i] = '\0';

    printf("Original Message: %s", cipher);
    printf("\nKey: %s", keyword);
    printf("\nNew Generated Key: %s", newkeyword);
    printf("\nDecrypted Message: %s", decryptedcipher);
}

