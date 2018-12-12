#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>

int i, j, lenText, lenKey;
char str[100], key[100], finalKey[100], result[100], type;

int main()
{
    printf("Chose an option: \n");
    printf("0 - Encrypt \n");
    printf("1 - Decrypt \n");
    scanf(" %d", &type);

    while((type < 0) || (type > 1))
    {
        printf("Wrong option! %d \n",type);
        printf("Chose an option: \n");
        printf("0 - Encrypt \n");
        printf("1 - Decrypt \n");
        scanf("%d", &type);
    }

    if(type==0)
    {
        loop_text:
        printf("\nEnter the text to encrypt: ");
        scanf(" %s", str);
        lenText = strlen(str);
        for(i = 0; i < lenText; ++i)
        {
            if(isalpha(str[i]) == false)
            {
                printf("Please enter only alphabet letters.\n");
                goto loop_text;
            }
        }

        loop_key:
        printf("\nEnter the encryption key: ");
        scanf(" %s", key);
        lenKey = strlen(key);
        for(j = 0; j < lenKey; ++j)
        {
            if(isalpha(key[j]) == false)
            {
                printf("Please enter only alphabet letters.\n");
                goto loop_key;
            }
        }

        for(i = 0, j = 0; i < lenText; ++i, ++j)
        {
            if(j == lenKey)
            {
                j = 0;
            }

            finalKey[i] = key[j];
        }

        finalKey[i] = '\0';
        i = 0;

        while(i < lenText)
        {
            result[i] = (26 + toupper(finalKey[i]) -  (toupper(str[i]))) % 26 + 'A';
            i += 1;
        }

        result[i] = '\0';
        printf("\nThe plain text was: %s\n", str);
        printf("The encryption key was: %s\n", key);
        printf("The encrypted  text is: %s\n", result);
    }
    else if(type==1)
    {
        loop_text1:
        printf("\nEnter the text to decrypt: ");
        scanf(" %s", str);
        lenText = strlen(str);
        for(i = 0; i < lenText; ++i)
        {
            if(isalpha(str[i]) == false)
            {
                printf("Please enter only alphabet letters.\n");
                goto loop_text1;
            }
        }
        loop_key1:
         printf("\nEnter the decryption key: ");
        scanf(" %s", key);
        lenKey = strlen(key);
        for(j = 0; j < lenKey; ++j)
        {
            if(isalpha(key[j]) == false)
            {
                printf("Please enter only alphabet letters.\n");
                goto loop_key1;
            }
        }

        for(i = 0, j = 0; i < lenText; ++i, ++j)
        {
            if(j == lenKey)
            {
                j = 0;
            }

            finalKey[i] = key[j];
        }

        finalKey[i] = '\0';
        i = 0;

        while(i < lenText)
        {
            result[i] = (26 + toupper(finalKey[i]) -  (toupper(str[i]))) % 26 + 'A';
            i += 1;
        }

        result[i] = '\0';
        printf("\nThe encrypted  text was: %s\n", str);
        printf("The decryption key was: %s\n", key);
        printf("The decrypted text is: %s\n", result);
    }
}