#include<fstream>
#include <string>
#include<vector>
#include<deque>
#include<queue>
#include<algorithm>
using namespace std;

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

void encryptbifid(const char* plainText, char* encryptedText, int len, const char* key, int keylen, int period)
{
	char matrix[5][5];

	int charpos[26][2];

	int rowcolresult[1000];

	generateMatrix(key, keylen, matrix);

	for(int i=0;i<5;++i)
		for (int j = 0; j < 5; ++j)
		{
			if (matrix[i][j] == 'I')
			{
				charpos[matrix[i][j] - 'A'][0] = i;
				charpos[matrix[i][j] - 'A'][1] = j;

				charpos['J' - 'A'][0] = i;
				charpos['J' - 'A'][1] = j;
			}
			else if (matrix[i][j] == 'J')
			{
				charpos[matrix[i][j] - 'A'][0] = i;
				charpos['I' - 'A'][1] = j;
			}
			else
			{
				charpos[matrix[i][j] - 'A'][0] = i;
				charpos[matrix[i][j] - 'A'][1] = j;
			}
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
		
	}

	for (int i = 0; i < len * 2; i+=2)
	{
		encryptedText[i / 2] = matrix[rowcolresult[i]][rowcolresult[i + 1]];
	}

}

void decryptbifid(const char* encryptedText, char* plainText, int len, const char* key, int keylen, int period)
{

	char matrix[5][5];

	int charpos[26][2];

	int rowcolresult[1000];

	generateMatrix(key, keylen, matrix);

	for (int i = 0; i<5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			if (matrix[i][j] == 'I')
			{
				charpos[matrix[i][j] - 'A'][0] = i;
				charpos[matrix[i][j] - 'A'][1] = j;

				charpos['J' - 'A'][0] = i;
				charpos['J' - 'A'][1] = j;
			}
			else if (matrix[i][j] == 'J')
			{
				charpos[matrix[i][j] - 'A'][0] = i;
				charpos['I' - 'A'][1] = j;
			}
			else
			{
				charpos[matrix[i][j] - 'A'][0] = i;
				charpos[matrix[i][j] - 'A'][1] = j;
			}
		}
	int k = 0;
	for (int i = 0; i < len; i++)
	{
		rowcolresult[k++] = charpos[encryptedText[i] - 'A'][0];
		rowcolresult[k++] = charpos[encryptedText[i] - 'A'][1];

	}
	k = 0;
	for (int i = 0; i < len*2; i+= period*2)
	{
		if (len*2 - i >= period * 2)
		{
			for (int j = 0; j < period; ++j)
			{
				plainText[k++] = matrix[rowcolresult[i+j]][rowcolresult[i + period + j]];
			}
		}
		else
		{
			for (int j = 0; j < (len*2- i)/2; ++j)
			{
				plainText[k++] = matrix[rowcolresult[i + j]][rowcolresult[i + (len*2 - i) / 2 + j]];
			}
		}
	}

}


int main()
{
	char plainText[50];
	char cipher[30];
	char decipher[30];
	char key[30];

	printf("Plain Text: ");
	gets_s(plainText, sizeof(plainText));

	printf("Key: ");
	gets_s(key, sizeof(plainText));

	int length = strlen(plainText);

	encryptbifid(plainText, cipher, length, key, strlen(key), 5);

	if (length % 2 == 1)
		++length;
	cipher[length] = '\0';


	printf("Encrypted Text: %s\n", cipher);

	decryptbifid(cipher, decipher, length, key, strlen(key), 5);

	decipher[length] = '\0';

	printf("Decrypted Text: %s", decipher);
	return 0;

}
