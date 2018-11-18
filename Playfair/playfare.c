#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>

int removerepeated(int size, int a[]);
void insertelementat(int position, int a[],int size);

int i, j, k, numstr[100], numcipher[100], numkey[100], lenkey, templen, flag=-1, size,cipherkey[5][5], lennumstr, row1, row2, col1, col2;
char str[100], key[100], option;

int removerepeated(int size, int a[])
{
    int i, j, k;
    for(i=0; i<size; ++i)
    {
        for(j=i+1; j<size;)
        {
            if(a[i]==a[j])
            {
                for(k=j; k<size; ++k)
                {
                    a[k]=a[k+1];
                }

                size -= 1;
            }
            else
            {
                j += 1;
            }
        }
    }

    return(size);
}

void insertelementat(int position, int a[], int size)
{
    int i, insitem=23, temp[size+1];
    for(i=0; i<=size; ++i)
    {
        if(i<position)
        {
            temp[i] = a[i];
        }
        else if(i>position)
        {
         temp[i] = a[i-1];
        }
        else if(i==position)
        {
            temp[i] = insitem;
        }
        else
        {
            /*Do nothing*/
        }
    }

    for(i=0; i<=size; ++i)
    {
        a[i] = temp[i];
    }
}

void encryption_method(void)
{
        loop_encrypt_text:
        printf("\nEnter your text: ");
        scanf(" %s", str);
        for(i=0, j=0; i<strlen(str); ++i)
        {
            if(isalpha(str[i])==false)
            {
                printf("Only alphabet letters allowed. Try again!\n");
                goto loop_encrypt_text;
            }
            else
            {
                /*Do nothing*/
            }

            if(str[i]!=' ')
            {
                str[j]=toupper(str[i]);
                j += 1;
            }
            else
            {
                /*Do nothing*/
            }
        }

        str[j]='\0';
        size=strlen(str);
        for(i=0; i<size; ++i)
        {
            if(str[i]!=' ')
            {
                numstr[i]=str[i]-'A';
            }
            else
            {
                /*Do nothing*/
            }
        }

        lennumstr=i;
        loop_encryption_key:
        printf("\nEncryption key: ");
        scanf(" %s", key);
        for(i=0, j=0; i<strlen(key); ++i)
        {
            if(isalpha(key[i])==false)
            {
                printf("Only alphabet letters allowed. Try again!\n");
                goto loop_encryption_key;
            }
            else
            {
                /*Do nothing*/
            }

            if(key[i]!=' ')
            {
                key[j]=toupper(key[i]);
                j += 1;
            }
            else
            {
                /*Do nothing*/
            }
        }

        key[j]='\0';
        k = 0;
        for(i=0; i<strlen(key)+26; ++i)
        {
            if(i<strlen(key))
            {
                if(key[i]=='J')
                {
                    flag = 8;
                    printf("%d",flag);
                }
                else
                {
                    /*Do nothing*/
                }

                numkey[i] = key[i]-'A';
            }
            else
            {
                if(k!=9 && k!=flag)
                {
                    numkey[i] = k;
                }
                else
                {
                    /*Do nothing*/
                }

                k += 1;
            }
        }

        templen = i;
        lenkey = removerepeated(templen, numkey);
        printf("\n");
        k = 0;
        for(i=0; i<5; ++i)
        {
            for(j=0; j<5; ++j)
            {
                cipherkey[i][j] = numkey[k];
                k += 1;
            }
        }

        printf("Password matrix is: \n");
        for(i=0; i<5; ++i)
        {
            for(j=0; j<5; ++j)
            {
                printf("%c ",cipherkey[i][j]+'A');
            }

            printf("\n");
        }

        for(i=0; i<lennumstr; i+=2)
        {
            if(numstr[i]==numstr[i+1])
            {
                insertelementat(i+1,numstr,lennumstr);
                lennumstr += 1;
            }
            else
            {
                /*Do nothing*/
            }
        }

        if(lennumstr%2!=0)
        {
            insertelementat(lennumstr,numstr,lennumstr);
            lennumstr += 1;
        }
        else
        {
            /*Do nothing*/
        }

        for(k=0; k<lennumstr; k+=2)
        {
            for(i=0; i<5; ++i)
            {
                for(j=0; j<5; ++j)
                {
                    if(numstr[k]==cipherkey[i][j])
                    {
                        row1 = i;
                        col1 = j;
                    }
                    else if(numstr[k+1]==cipherkey[i][j])
                    {
                        row2 = i;
                        col2 = j;
                    }
                    else
                    {
                        /*Do nothing*/
                    }
                }
            }

            if(row1==row2)
            {
                col1= (col1+1) % 5;
                col2= (col2+1) % 5;
                numcipher[k] = cipherkey[row1][col1];
                numcipher[k+1] = cipherkey[row2][col2];
            }
            else if(col1==col2)
            {
                row1= (row1+1) % 5;
                row2= (row2+1) % 5;
                numcipher[k] = cipherkey[row1][col1];
                numcipher[k+1] = cipherkey[row2][col2];
            }
            else if(row1!=row2&&col1!=col2)
            {
                numcipher[k] = cipherkey[row1][col2];
                numcipher[k+1] = cipherkey[row2][col1];
            }
            else
            {
                /*Do nothing*/
            }
        }

        printf("\nPlain text is: %s\n", str);
        printf("Encryption key is: %s\n", key);
        printf("Cipher text is: ");
        for(i=0; i<lennumstr; ++i)
        {
            printf("%c",numcipher[i]+'A');
        }

        printf("\n");
}

void decryption_method(void)
{
        loop_decrypt_text:
        printf("\nPlease enter a cipher text to decrypt: ");
        scanf(" %s", str);
        for(i=0, j=0; i<strlen(str); ++i)
        {
            if(isalpha(str[i])==false)
            {
                printf("Only alphabet letters allowed. Try again!\n");
                goto loop_decrypt_text;
            }
            else
            {
                /*Do nothing*/
            }

            if(str[i]!=' ')
            {
                str[j]=toupper(str[i]);
                j += 1;
            }
            else
            {
                /*Do nothing*/
            }
        }

        str[j]='\0';
        size=strlen(str);
        for(i=0; i<size; ++i)
        {
            if(str[i]!=' ')
            {
                numstr[i]=str[i]-'A';
            }
            else
            {
                /*Do nothing*/
            }
        }

        lennumstr=i;
        loop_decryption_key:
        printf("\nDecryption key: ");
        scanf(" %s", key);
        for(i=0, j=0; i<strlen(key); ++i)
        {
            if(isalpha(key[i])==false)
            {
                printf("Only alphabet letters allowed. Try again!\n");
                goto loop_decryption_key;
            }
            else
            {
                /*Do nothing*/
            }

            if(key[i]!=' ')
            {
                key[j]=toupper(key[i]);
                j += 1;
            }
            else
            {
                /*Do nothing*/
            }
        }

        key[j]='\0';
        k = 0;
        for(i=0; i<strlen(key)+26; ++i)
        {
            if(i<strlen(key))
            {
                if(key[i]=='J')
                {
                    flag = 8;
                    printf("%d",flag);
                }
                else
                {
                    /*Do nothing*/
                }

                numkey[i] = key[i]-'A';
            }
            else
            {
                if(k!=9 && k!=flag)
                {
                    numkey[i] = k;
                }
                else
                {
                    /*Do nothing*/
                }

                k += 1;
            }
        }

        templen = i;
        lenkey = removerepeated(templen, numkey);
        printf("\n");
        k = 0;
        for(i=0; i<5; ++i)
        {
            for(j=0; j<5; ++j)
            {
                cipherkey[i][j]=numkey[k];
                k += 1;
            }
        }

        printf("Password matrix is: \n");
        for(i=0; i<5; ++i)
        {
            for(j=0; j<5; ++j)
            {
                printf("%c ",cipherkey[i][j]+'A');
            }

            printf("\n");
        }

        for(i=0; i<lennumstr; i+=2)
        {
            if(numstr[i]==numstr[i+1])
            {
                insertelementat(i+1,numstr,lennumstr);
                lennumstr += 1;
            }
            else
            {
                /*Do nothing*/
            }
        }

        if(lennumstr%2!=0)
        {
            insertelementat(lennumstr,numstr,lennumstr);
            lennumstr += 1;
        }
        else
        {
            /*Do nothing*/
        }

        for(k=0; k<lennumstr; k+=2)
        {
            for(i=0; i<5; ++i)
            {
                for(j=0; j<5; ++j)
                {
                    if(numstr[k]==cipherkey[i][j])
                    {
                        row1 = i;
                        col1 = j;
                    }
                    else if(numstr[k+1]==cipherkey[i][j])
                    {
                        row2 = i;
                        col2 = j;
                    }
                    else
                    {
                        /*Do nothing*/
                    }
                }
            }

            if(row1==row2)
            {
                col1= (col1-1) % 5;
                col2= (col2-1) % 5;
                if(col1<0)
                {
                    col1= 5 + col1;
                }
                else if(col2<0)
                {
                    col2 = 5 + col2;
                }
                else
                {
                    /*Do nothing*/
                }

                numcipher[k] = cipherkey[row1][col1];
                numcipher[k+1] = cipherkey[row2][col2];
            }
            else if(col1==col2)
            {
                row1= (row1-1) % 5;
                row2= (row2-1) % 5;
                if(row1<0)
                {
                    row1 = 5 + row1;
                }
                else if(row2<0)
                {
                    row2 = 5 + row2;
                }
                else
                {
                    /*Do nothing*/
                }

                numcipher[k] = cipherkey[row1][col1];
                numcipher[k+1] = cipherkey[row2][col2];
            }
            else if(row1!=row2&&col1!=col2)
            {
                numcipher[k] = cipherkey[row1][col2];
                numcipher[k+1] = cipherkey[row2][col1];
            }
            else
            {
                /*Do nothing*/
            }
        }

        printf("\nThe cipher text is: %s\n", str);
        printf("The decryption key is: %s\n", key);
        printf("The plain text is: ");
        for(i=0; i<lennumstr; ++i)
        {
            if((numcipher[i]+'A')!='X')
            {
                printf(" %c",numcipher[i]+'A');
            }
            else
            {
                /*Do nothing*/
            }
        }

        printf("\n");
}

int main()
{
    loop_main:
    printf("1.Encryption\n");
    printf("2.Decryption\n\n");
    scanf(" %c", &option);

    if(option=='1')
    {
        encryption_method();
    }
    else if(option=='2')
    {
        decryption_method();
    }
    else
    {
        printf("\nThe chosen option is not valid.\n");
        goto loop_main;
    }

    return 0;
}
