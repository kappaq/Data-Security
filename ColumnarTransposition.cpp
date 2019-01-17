#include<fstream>
#include <string>
#include<vector>
#include<deque>
#include<queue>
#include<algorithm>
using namespace std;


void encryptcolumnartransposition(const char* plainText, char* encryptedText, int len, const char* key, int keylen)
{
	char **matrix = (char**)malloc(keylen * sizeof(char*));

	char copy_key[100];

	memcpy(copy_key, key, keylen);

	for (int i = 0; i < keylen; ++i)
	{
		matrix[i] = (char*)malloc(len / keylen + (len%keylen!=0));
	}
	int nr_columns = keylen;
	int nr_lines = len / keylen + (len % keylen != 0);

	int k = 0;
	for(int i=0;i<nr_lines;++i)
		for (int j = 0; j < nr_columns; ++j)
		{
			if(k<len)
				matrix[j][i] = plainText[k++];
			else
				matrix[j][i] = 'X';
		}

	for (int i = 0; i < keylen - 1; ++i)
	{
		for (int j = i + 1; j < keylen; ++j)
		{
			if (copy_key[i] > copy_key[j])
			{
				char cpy = copy_key[i];
				copy_key[i] = copy_key[j];
				copy_key[j] = cpy;

				char *cpy_pt = matrix[i];
				matrix[i] = matrix[j];
				matrix[j] = cpy_pt;
			}
		}
	}

	k = 0;
	for (int j = 0; j < nr_columns; ++j)
		for (int i = 0; i<nr_lines; ++i)
		{
			encryptedText[k++] = matrix[j][i];
		}

	for (int i = 0; i < keylen; ++i)
		free(matrix[i]);

	free(matrix);

}

void decryptcolumnartransposition(const char* encryptedText, char* plainText, int len, const char* key, int keylen)
{
	char **matrix = (char**)malloc(keylen * sizeof(char*));

	char **copy_matrix = (char**)malloc(keylen * sizeof(char*));;

	char copy_key[100];

	int indexes[100];

	memcpy(copy_key, key, keylen);
	
	for (int i = 0; i < keylen; ++i)
		indexes[i] = i;

	for (int i = 0; i < keylen; ++i)
	{
		matrix[i] = (char*)malloc(len / keylen + (len%keylen != 0));
	}
	int nr_columns = keylen;
	int nr_lines = len / keylen + (len % keylen != 0);

	int k = 0;
	for (int j = 0; j < nr_columns; ++j)
		for (int i = 0; i<nr_lines; ++i)
		{
				matrix[j][i] = encryptedText[k++];
		}


	for (int i = 0; i < keylen - 1; ++i)
	{
		for (int j = i + 1; j < keylen; ++j)
		{
			if (copy_key[i] > copy_key[j])
			{
				char cpy = copy_key[i];
				copy_key[i] = copy_key[j];
				copy_key[j] = cpy;

				int idx = indexes[i];
				indexes[i] = indexes[j];
				indexes[j] = idx;
			}
		}
	}

	for (int i = 0; i < keylen; ++i)
	{
		copy_matrix[indexes[i]] = matrix[i];
	}

	k = 0;
	for (int i = 0; i < nr_lines;++i)
	{
		for (int j = 0; j < nr_columns; ++j)
		{
			plainText[k++] = copy_matrix[j][i];
		}
	}
	for (int i = 0; i < keylen; ++i)
		free(matrix[i]);

	free(matrix);
	free(copy_matrix);
}


int main()
{
	char plainText[50];
	char cipher[50];
	char decipher[50];
	char key[50];

	printf("Plain Text: ");
	gets_s(plainText, sizeof(plainText));

	printf("Key: ");
	gets_s(key, sizeof(plainText));

	int length = strlen(plainText);

	int keyLength = strlen(key);

	encryptcolumnartransposition(plainText, cipher, length, key, keyLength);

	length = length + length / keyLength * keyLength + (length % keyLength != 0)*keyLength - length;

	cipher[length] = '\0';


	printf("Encrypted Text: %s\n", cipher);

	decryptcolumnartransposition(cipher, decipher, length, key, keyLength);

	decipher[length] = '\0';

	printf("Decrypted Text: %s", decipher);
	return 0;

}
