#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void generateMatrix(const char* key, int keylen, char matrix[5][5])
{
	char freq[26];
	int nr = 0;
	memset(freq, 0, sizeof(freq));
	for (int i = 0; i < keylen; ++i)
	{
		if (freq[key[i] - 'A'] == 0)
		{
			freq[key[i] - 'A'] = 1;

			if (key[i] == 'I')
			{
				freq['J' - 'A'] = 1;
			}
			else if (key[i] == 'J')
			{
				freq['I' - 'A'] = 1;
			}

			matrix[nr / 5][nr % 5] = key[i];
			++nr;
		}
	}

	if (freq['J' - 'A'] == 0 && freq['I' - 'A'] == 0)
		freq['J' - 'A'] = 1;

	for (int i = 0; i < 26; ++i)
	{
		if (freq[i] == 0)
		{
			matrix[nr / 5][nr % 5] = i + 'A';
			++nr;
		}
	}
}

void encryptfoursquare(const char* plainText, char* encryptedText, int len, const char* key1, int keylen1, const char* key2, int keylen2)
{
	char matrix1[5][5];
	char matrix2[5][5];
	char matrix3[5][5];
	char matrix4[5][5];


	char pos_letter[26][2];

	generateMatrix("", 0, matrix1);
	generateMatrix(key1, keylen1, matrix2);
	generateMatrix(key2, keylen2, matrix3);
	generateMatrix("", 0, matrix4);

	

	for (int i = 0; i < len; i+=2)
	{

		int i1 = (plainText[i] >= 'J') ? ((plainText[i]-'A'-1)/5) : ((plainText[i]-'A')/5);
		int j1 = (plainText[i] >= 'J') ? ((plainText[i]-'A' - 1) % 5) : ((plainText[i]-'A') % 5);

		int i2 = (plainText[i + 1] >= 'J') ? ((plainText[i + 1]-'A' - 1) / 5) : ((plainText[i + 1]-'A') / 5);
		int j2 = (plainText[i + 1] >= 'J') ? ((plainText[i + 1]-'A' - 1) % 5) : ((plainText[i + 1]-'A') % 5);


		encryptedText[i] = matrix2[i1][j2];
		encryptedText[i + 1] = matrix3[i2][j1];

	}

}

void decryptfoursquare(const char* encryptedText, char* plainText, int len, const char* key1, int keylen1, const char* key2, int keylen2)
{

	char matrix1[5][5];
	char matrix2[5][5];
	char matrix3[5][5];
	char matrix4[5][5];

	int position2[26][2];
	int position3[26][2];


	char pos_letter[26][2];

	generateMatrix("", 0, matrix1);
	generateMatrix(key1, keylen1, matrix2);
	generateMatrix(key2, keylen2, matrix3);
	generateMatrix("", 0, matrix4);
	

	for(int i=0;i<5;++i)
		for (int j = 0; j < 5; ++j)
		{
			position2[matrix2[i][j] - 'A'][0] = i;
			position2[matrix2[i][j] - 'A'][1] = j;
		}

	for (int i = 0; i<5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			position3[matrix3[i][j] - 'A'][0] = i;
			position3[matrix3[i][j] - 'A'][1] = j;
		}



	for (int i = 0; i < len; i += 2)
	{

		int i1 = position2[encryptedText[i]- 'A'][0];
		int j1 = position2[encryptedText[i] - 'A'][1];

		int i2 = position3[encryptedText[i+1] - 'A'][0];
		int j2 = position3[encryptedText[i+1] - 'A'][1];


		plainText[i] = matrix1[i1][j2];
		plainText[i + 1] = matrix4[i2][j1];

	}
}

int main()
{
	char plainText[100];
	char cipher[100];
	char decipher[100];
	char key1[100];
	char key2[100];
	printf("Plain Text: ");
	gets_s(plainText, sizeof(plainText));

	printf("Key1: ");
	gets_s(key1, sizeof(plainText));

	printf("Key2: ");
	gets_s(key2, sizeof(plainText));

	int length = strlen(plainText);

	


	if (length % 2 == 1)
	{
		++length;
		plainText[length] = '\0';
		plainText[length - 1] = 'X';
	}

	encryptfoursquare(plainText, cipher, length, key1, strlen(key1), key2, strlen(key2));

	cipher[length] = '\0';

	printf("Encrypted Text: %s\n", cipher);

	decryptfoursquare(cipher, decipher, length, key1, strlen(key1), key2, strlen(key2));

	decipher[length] = '\0';

	printf("Decrypted Text: %s", decipher);
	return 0;
}
