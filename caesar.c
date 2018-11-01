#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "caesarinfo.h"

void encrypt(char cipher[], int shift){

    int i;
    char x;

    for( i = 0; cipher[i] != '\0'; ++i ){

        x = cipher[i];

        if( x >= 'a' && x <= 'z' ){

            x = x + shift;

            if( x > 'z' ){

                x = x - 'z' + 'a' - 1;

            }

            cipher[i] = x;

        }

        else if( x >= 'A' && x <= 'Z'){

             x = x + shift;

             if( x > 'Z' ){

                x = x - 'Z' + 'A' - 1;

            }

            cipher[i] = x;
        }
    }

    printf("Encrypted cipher: %s ", cipher);

}



void decrypt(char cipher[], int shift){

    int i;
    char x;

    for( i = 0; cipher[i] != '\0'; ++i ){

        x = cipher[i];

        if( x >= 'a' && x <= 'z' ){

            x = x - shift;

            if( x < 'a' ){

                x = x + 'z' - 'a' + 1;

            }

            cipher[i] = x;

        }

        else if( x >= 'A' && x <= 'Z'){

             x = x - shift;

             if( x < 'A' ){

                x = x + 'Z' - 'A' + 1;

            }

            cipher[i] = x;
        }
    }

    printf("Decrypted cipher: %s ", cipher);

}
