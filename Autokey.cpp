#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void encryptVigenere(const char* plainText, char* encryptedText, int len, const char* key)
{
	for (int i = 0; i < len; i++)
		encryptedText[i] = 'A' + (plainText[i] - 'A' + key[i] - 'A') % 26;
}

void decryptVigenere(const char* encryptedText, char* plainText, int len, const char* key)
{
	for (int i = 0; i < len; i++)
		plainText[i] = 'A' + (26 + encryptedText[i] - key[i]) % 26;
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

	int l1 = strlen(plainText);
	int l2 = strlen(key);
	int j = 0;
	while (l2 < l1)
		key[l2++] = plainText[j++];

	int length = strlen(plainText);

	encryptVigenere(plainText, cipher, length, key);

	cipher[length] = '\0';


	printf("Encrypted Text: %s\n", cipher);

	decryptVigenere(cipher, decipher, length, key);

	decipher[length] = '\0';

	printf("Decrypted Text: %s", decipher);
	return 0;
}
