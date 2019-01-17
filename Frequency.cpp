#include<stdio.h>
#include<string.h>
using namespace std;
char str[100];

struct character
{
	char c;
	int fr;
};

void printFrequency(char *s, int len)
{
	int freq[26];
	character P[100];

	memset(P, 0, sizeof(P));

	memset(freq, 0, sizeof(freq));

	for (int i = 0; i < len; i++)
		freq[s[i] - 'A']++;

	for (int i = 0; i < 26; i++)
		if (freq[i] != 0)
		{
			character ch;
			ch.c = i + 'A';
			ch.fr = freq[i];
			
			P[i] = ch;
		}
	
	for(int i=0;i<25;++i)
		for (int j = i + 1; j < 25; ++j)
		{
			if (P[i].fr < P[j].fr)
			{
				character temp = P[i];

				P[i] = P[j];
				P[j] = temp;
			}
		}

	for (int i = 0; i < 26; ++i)
	{
		if(P[i].fr!=0)
			printf("%c:%d\n", P[i].c, P[i].fr);
	}
}

int main()
{
	printf("The string:");
	scanf("%s", str);
	printFrequency(str, strlen(str));
	return 0;
}
