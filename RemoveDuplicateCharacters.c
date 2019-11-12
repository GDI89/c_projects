// Function that create a list of unique words

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;
typedef struct Item{
	string Word;
	struct Item *NextWord;
} Item;

typedef struct Item *ListItem;
typedef ListItem ListString;
ListString List;
string lastWord;

void CreateItem();
void ExcludeItem();
void PrintItem();
int Count();

int main(void) {
	printf("Enter some words separated by spaces or tabs: \n");
	CreateItem();
	ExcludeItem();
	printf("\nTransform string: \n");
	PrintItem();
	return 0;
}

void CreateItem()
{
	ListItem itemLst;
	lastWord = (string)malloc(1*sizeof(char));
	if (scanf("%c", lastWord) == EOF)
	{
		free(lastWord);
		return;
	}
	
	List = itemLst = (Item*)malloc(sizeof(Item));
	itemLst -> Word = lastWord;
	itemLst -> NextWord = NULL;
	
	printf("%s", itemLst -> Word);
	lastWord = (string)malloc(1*sizeof(char));
	
	while(scanf("%c", lastWord) != EOF)
	{
		itemLst = itemLst -> NextWord = (Item*)malloc(sizeof(Item));
		itemLst -> Word = lastWord;
		itemLst -> NextWord = NULL;
		printf("%s", itemLst -> Word);
		lastWord = (string)malloc(1*sizeof(char));
	}
	free(lastWord);
	lastWord = itemLst -> Word;
}

int Count()
{
	int counter;
	ListString currentList = List;
	for(counter = 0; currentList != NULL; currentList = currentList -> NextWord, counter++);
	return counter;
}

void ExcludeItem()
{
	ListItem deletedItem = NULL;
	ListItem previousItem = NULL;
	
	if (List == NULL) return;
	ListItem currentItem = List;
	
	while(currentItem -> NextWord != NULL)
	{
		if (strcmp(currentItem -> Word, currentItem -> NextWord -> Word) == 0)
		{
			if (currentItem == List)
			{
				deletedItem = currentItem;
				currentItem = List = List -> NextWord;
			}
			else
			{
				previousItem -> NextWord = currentItem -> NextWord;
				deletedItem = currentItem;
				currentItem = previousItem -> NextWord;
			}
			free(deletedItem -> Word);
			free(deletedItem);
		}
		else
		{
			previousItem = currentItem;
			currentItem = currentItem -> NextWord;
		}
	}
}

void PrintItem()
{
	ListString currentItem = List;
	while (currentItem != NULL)
	{
		ListString previous = currentItem;
		printf("%s", currentItem -> Word);
		currentItem = currentItem -> NextWord;
		free(previous -> Word);
		free(previous);
	}
}