#include<fstream>
#include <string>
#include<vector>
#include<deque>
#include<queue>
#include<algorithm>
#include<string.h>
using namespace std;

void generateMatrix(const char* key, int keylen, char matrix[3][3][3])
{
	char freq[27];
	int nr = 0;
	memset(freq, 0, sizeof(freq));
	for (int i = 0; i < keylen; ++i)
	{
		if (freq[key[i] - 'A'] == 0)
		{
			freq[key[i] - 'A'] = 1;

			matrix[nr / 9][nr % 9 / 3][nr%3] = key[i];
			++nr;
		}
	}


	for (int i = 0; i < 27; ++i)
	{
		if (freq[i] == 0)
		{
			matrix[nr / 9][nr % 9 / 3][nr%3] = i + 'A';
			++nr;
		}
	}
}

void encrypttrifid(const char* plainText, char* encryptedText, int len, const char* key, int keylen, int period)
{
	char matrix[3][3][3];

	int charpos[27][3];

	int rowcolresult[1000];

	generateMatrix(key, keylen, matrix);

	for(int i =0 ; i < 3 ; ++i)
		for (int j = 0; j < 3; ++j)
            for(int k = 0; k < 3; ++k)
		{
			charpos[matrix[i][j][k] - 'A'][0] = i;
			charpos[matrix[i][j][k] - 'A'][1] = j;
            charpos[matrix[i][j][k] - 'A'][2] = k;
		}
	int k = 0;
	for (int i = 0; i < len; i+=period)
	{
		for (int j = 0; j < period && i+j<len; ++j)
		{
			rowcolresult[k++] = charpos[plainText[i+j] - 'A'][0];
		}
		for (int j = 0; j < period && i+j<len; ++j)
		{
			rowcolresult[k++] = charpos[plainText[i+j] - 'A'][1];
		}

        for (int j = 0; j < period && i+j<len; ++j)
		{
			rowcolresult[k++] = charpos[plainText[i+j] - 'A'][2];
		}
		
	}

	for (int i = 0; i < len * 3; i+=3)
	{
		encryptedText[i / 3] = matrix[rowcolresult[i]][rowcolresult[i + 1]][rowcolresult[i + 2]];
	}

}

void decrypttrifid(const char* encryptedText, char* plainText, int len, const char* key, int keylen, int period)
{

	char matrix[3][3][3];

	int charpos[27][3];

	int rowcolresult[1000];

	generateMatrix(key, keylen, matrix);

	for(int i =0 ; i < 3 ; ++i)
		for (int j = 0; j < 3; ++j)
            for(int k = 0; k < 3; ++k)
		{
			charpos[matrix[i][j][k] - 'A'][0] = i;
			charpos[matrix[i][j][k] - 'A'][1] = j;
            charpos[matrix[i][j][k] - 'A'][2] = k;
		}

	int k = 0;
	for (int i = 0; i < len; i++)
	{
		rowcolresult[k++] = charpos[encryptedText[i] - 'A'][0];
		rowcolresult[k++] = charpos[encryptedText[i] - 'A'][1];
        rowcolresult[k++] = charpos[encryptedText[i] - 'A'][2];

	}
	k = 0;
	for (int i = 0; i < len*3; i+= period*3)
	{
		if (len*3 - i >= period * 3)
		{
			for (int j = 0; j < period; ++j)
			{
				plainText[k++] = matrix[rowcolresult[i+j]][rowcolresult[i + period + j]][rowcolresult[i + period*2 + j]];
			}
		}
		else
		{
			for (int j = 0; j < (len*3- i)/3; ++j)
			{
				plainText[k++] = matrix[rowcolresult[i + j]][rowcolresult[i + (len*3 - i) / 3 + j]][rowcolresult[i + (len*3 - i) / 3 * 2 + j]];
			}
		}
	}

}


int main()
{
	char plainText[60];
	char cipher[60];
	char decipher[60];
	char key[60];
	printf("Plain Text: ");
	gets(plainText);

	printf("Key: ");
	gets(key);


	int length = strlen(plainText);

	encrypttrifid(plainText, cipher, length, key, strlen(key), 5);

    cipher[length] = '\0';

	printf("Encrypted Text: %s\n", cipher);

    

	decrypttrifid(cipher, decipher, length, key, strlen(key), 5);

	decipher[length] = '\0';

	printf("Decrypted Text: %s", decipher);

    system("pause");

   
	return 0;

}
