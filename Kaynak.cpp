#include <stdio.h>
#include <string.h>

int menu()
{
	int choice;
	printf("MENU\n***********\n1. [Find first occurence]\n2. [Find last occurence]\n3. [Find all occurences]\n4. [Delete first occurence]\n5. [Delete all occurences]\n6. [Replace first occurence]\n7. [Replace all occurences]");
	printf("\n[Enter your choice]:");
	scanf("%d", &choice);
	while (choice < 1 || choice > 7)
	{
		printf("\n[Enter your choice]:");
		scanf("%d", &choice);
	}
	return choice;
}

int findFirstOcc(char yourText[], char word[])
{
	int sentlen = strlen(yourText), wordlen = strlen(word), k;
	for (k = 0; k < sentlen; k++)
	{
		if (strncmp(yourText + k, word, wordlen) == 0)
			return k;
	}
	return -1;
}

int findLastOcc(char yourText[], char word[])
{
	int sentlen = strlen(yourText), wordlen = strlen(word), k;
	for (k = sentlen; k > wordlen; k--)
	{
		if (strncmp(yourText + k, word, wordlen) == 0)
			return k;
	}
	return -1;
}

int findAllOcc(char yourText[], char word[], int occ[])
{
	int sentlen = strlen(yourText), wordLen = strlen(word), k, count = 0;
	for (k = 0; k < sentlen; k++)
	{
		if (strncmp(yourText + k, word, wordLen) == 0)
		{
			occ[count] = k;
			count++;
		}
	}
	if (count != 0)
		return count;
	else return -1;
}

int findAllWord(char yourText[], char word[], int occ[])
{
	int k, count = 0;
	for (k = 0; k < strlen(yourText); k++)
	{
		if (strncmp(yourText + k, word, strlen(word)) == 0)
		{
			if ((k == 0 && yourText[k + strlen(word)] == ' ') || (yourText[k - 1] == ' ' && yourText[k + strlen(word)] == ' ') || (yourText[k - 1] == ' ' && yourText[k + strlen(word)] == '\0'))
			{
				occ[count] = k;
				count++;
			}
		}
	}
	if (count != 0)
		return count;
	else return -1;
}

int deleteFirstOcc(char yourText[], char word[])
{
	int what = 0;
	int pos = findFirstOcc(yourText, word);
	if (pos != -1)
	{
		char before[1000] = " ", after[1000] = " ";
		strncpy(before, yourText, pos);
		before[pos] = '\0';
		strcpy(after, yourText + pos + strlen(word));
		strcat(before, after);
		strcpy(yourText, before);
		what++;
	}
	if (what == 0)
		return -1;
	else return what;
}

int findFirstWord(char yourText[], char word[])
{
	int i;
	for (i = 0; i < strlen(yourText); i++)
	{
		if ((strncmp(yourText + i, word, strlen(word)) == 0) && ((i == 0 && yourText[i + strlen(word)] == ' ') || (yourText[i - 1] == ' ' && yourText[i + strlen(word)] == ' ') || (yourText[i - 1] == ' ' && yourText[i + strlen(word)] == '\0')))
			return i;
	}
	return -1;
}

void deleteFirstWord(char yourText[], char word[])
{
	int pos = findFirstWord(yourText, word);
	if (pos != -1)
	{
		char before[1000] = " ", after[1000] = " ";
		strncpy(before, yourText, pos);
		before[pos] = '\0';
		strcpy(after, yourText + pos + strlen(word));
		strcat(before, after);
		strcpy(yourText, before);
	}
}

void deleteAllOcc(char yourText[], char word[])
{

	int sentlen = strlen(yourText), k;
	for (k = 0; k < sentlen; k++)
	{
		deleteFirstOcc(yourText, word);
	}

}
int deleteAllWords(char yourText[], char word[], int occ[], int count)
{
	int b = 0, i;
	int sentlen = strlen(yourText), k;
	for (k = 0; k < count; k++)
	{
		if ((occ[k] == 0 && yourText[occ[k] + strlen(word)] == ' ') || (yourText[occ[k] - 1] == ' ' && yourText[occ[k] + strlen(word)] == ' ') || (yourText[occ[k] - 1] == ' ' && yourText[occ[k] + strlen(word)] == '\0'))
		{
			deleteFirstWord(yourText, word);
			b++;
			for (i = 0; i < count; i++)
				occ[i] -= 3;
		}
	} return b;
}

void replaceFirstOcc(char yourText[], char word[], char replacement[])
{
	int pos = findFirstOcc(yourText, word);
	strcat(replacement, yourText + pos + strlen(word));
	strcpy(yourText + pos, replacement);
}

void replaceFirstWord(char yourText[], char word[], char replacement[], int pos)
{
	strcat(replacement, yourText + pos + strlen(word));
	strcpy(yourText + pos, replacement);
}

void replaceAllOcc(char yourText[], char word[], char replacement[])
{
	int pos = findFirstOcc(yourText, word);
	char temp[20];
	strcpy(temp, replacement);
	while (pos != -1)
	{
		strcat(replacement, yourText + pos + strlen(word));
		strcpy(yourText + pos, replacement);
		strcpy(replacement, temp);
		pos = findFirstOcc(yourText, word);
	}
}

void replaceAllWords(char yourText[], char word[], char replacement[])
{
	int pos = findFirstWord(yourText, word);
	char temp[20];
	strcpy(temp, replacement);
	while (pos != -1)
	{
		strcat(replacement, yourText + pos + strlen(word));
		strcpy(yourText + pos, replacement);
		strcpy(replacement, temp);
		pos = findFirstOcc(yourText, word);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	int option, match;
	char yourText[500], word[20], choice;
	FILE *inp;
	inp = fopen("yourText.txt", "r");
	if (inp == NULL)
		printf("Error opening text");
	else {
		while (fscanf(inp, "%[^\n]", yourText) != EOF);
		printf("Your Text\n--------------\n[%s]\n-------------\n[Harf sayisi]: %d", yourText, strlen(yourText));
		printf("\n[Type a word from the text above to search]:");
		scanf("%s", word);
		printf("\n[Do you want to search for an individual word? (Y/N)]:");
		scanf(" %c", &choice);
		while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
		{
			printf("\n[Just type Y or N]:");
			scanf(" %c", &choice);
		}
		option = menu();
		if (choice == 'N' || choice == 'n')
		{
			if (option == 1)
			{
				match = findFirstOcc(yourText, word);
				if (match == -1)
					printf("\n[Not a single match found]");
				else printf("[First match is at %d]", match);
			}
			else if (option == 2)
			{
				match = findLastOcc(yourText, word);
				if (match == -1)
					printf("\n[Not a single match found]");
				else printf("[Last match is at %d]", match);
			}
			else if (option == 3)
			{
				int a;
				int occ[50];
				match = findAllOcc(yourText, word, occ);
				if (match == -1)
					printf("\n[Not a single match found]");
				else {
					printf("\n[Matches found at]:");
					for (a = 0; a < match; a++)
						printf(" <%d> ", occ[a]);
				}
			}
			else if (option == 4)
			{
				match = deleteFirstOcc(yourText, word);
				if (match == -1)
					printf("\n[Not a single match found]");
				else {
					printf("\n[%s]", yourText);
				}

			}
			else if (option == 5)
			{
				match = findFirstOcc(yourText, word);
				if (match == -1)
					printf("\n[Not a single match found]");
				else {
					deleteAllOcc(yourText, word);
					printf("\n\n[%s]", yourText);
				}
			}
			else if (option == 6)
			{
				char replacement[500];
				match = findFirstOcc(yourText, word);
				if (match == -1)
					printf("\n[Not a single match found]");
				else {
					printf("\n[Type something to replace the first <%s> with]:", word);
					scanf("%s", replacement);
					replaceFirstOcc(yourText, word, replacement);
					printf("\n\n[%s]", yourText);
				}
			}
			else if (option == 7)
			{
				match = findFirstOcc(yourText, word);
				if (match == -1)
					printf("\n[Not a single match found]");
				else {
					char replacement[500];
					int occ[50];
					printf("\n[Type something to replace the all <%s>'s with]:", word);
					scanf("%s", replacement);
					replaceAllOcc(yourText, word, replacement);
					printf("\n\n[%s]", yourText);
				}
			}
		}
		else if (choice == 'Y' || choice == 'y')
		{
			if (option == 1)
			{
				int pos = findFirstOcc(yourText, word);
				if (pos == -1)
					printf("\n[There aren't any words like that]");
				else if ((pos == 0 && yourText[pos + strlen(word)] == ' ') || (yourText[pos - 1] == ' ' && yourText[pos + strlen(word)] == ' ') || (yourText[pos - 1] == ' ' && yourText[pos + strlen(word)] == '\0'))
					printf("\n[The first occurence of the word is at <%d>]", pos);
				else printf("\n[There aren't any words like that]");
			}
			else if (option == 2)
			{
				int pos = findLastOcc(yourText, word);
				if (pos == -1)
					printf("\n[There aren't any words like that]");
				else if ((pos == 0 && yourText[pos + strlen(word)] == ' ') || (yourText[pos - 1] == ' ' && yourText[pos + strlen(word)] == ' ') || (yourText[pos - 1] == ' ' && yourText[pos + strlen(word)] == '\0'))
					printf("\n[The last occurence of the word is at <%d>]", pos);
				else printf("\n[There aren't any words like that]");
			}
			else if (option == 3)
			{
				int occ[50], i;
				int count = findAllWord(yourText, word, occ);
				if (count == -1)
					printf("\n[There aren't any words like that]");
				else {
					printf("\n[All occurences of the word are at]");
					for (i = 0; i < count; i++)
						printf(" <%d>", occ[i]);
				}
			}
			else if (option == 4)
			{
				int pos = findFirstWord(yourText, word);
				if (pos == -1)
					printf("\n[There aren't any words like that]");
				else {
					deleteFirstWord(yourText, word);
					printf("\n[The new version of the text]: \n%s", yourText);
				}
			}
			else if (option == 5)
			{
				int occ[50];
				int pos = findFirstOcc(yourText, word);
				if (pos == -1)
					printf("\n[There aren't any words like that]");
				else {
					int count = findAllWord(yourText, word, occ);
					int b = deleteAllWords(yourText, word, occ, count);
					if (b == 0)
						printf("\n[There aren't any words like that]");
					else {
						printf("\n[The new version of the text]: \n%s", yourText);
					}
				}
			}
			else if (option == 6)
			{
				char replacement[500];
				int pos = findFirstWord(yourText, word);
				if (pos == -1)
					printf("\n[There aren't any words like that]");
				else {
					printf("\n[Type something to replace the first <%s> with]:", word);
					scanf("%s", replacement);
					replaceFirstWord(yourText, word, replacement, pos);
					printf("\n[The new version of the text]: \n%s", yourText);
				}
			}
			else if (option == 7)
			{
				char replacement[500];
				int pos = findFirstWord(yourText, word);
				if (pos == -1)
					printf("\n[There aren't any words like that]");
				else {
					printf("\n[Type something to replace all <%s>'s with]:", word);
					scanf("%s", replacement);
					replaceAllWords(yourText, word, replacement);
					printf("\n[The new version of the text]: \n%s", yourText);
				}
			}
		}
	}
}