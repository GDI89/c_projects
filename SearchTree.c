// Search tree. 
// +<non-negative number> - if number not exists in tree, then number added in tree
// -<non-negative number> - if number exists in tree, then number delete from tree
// ?<non-negative number> - if number exists in tree, then print {<number> yes}, else {<number> no}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//+28 +4 +7 +1 +13 + 54 +3 +10 +19 +5 +9 -13 -3 ?4 ?28 ?90

typedef char* string;
typedef struct Node{
	int NValue;
	struct Node* LNode;
	struct Node* RNode;
} Node;

typedef struct Node* TreeItem;
TreeItem RootNode;

void AddNode(int currentVal);
void DeleteNode(int currentVal);
void PrintTree(TreeItem node);
short Exists(TreeItem node, int searchItem);

int main()
{
	printf("Enter characters separated by spaces: ");
	char charAction;
	int currentDig;
	while((charAction = getchar()) != EOF)
	{
		scanf("%d", &currentDig);
		switch(charAction)
		{
			case '+':
				AddNode(currentDig);
				break;
			case '-':
				DeleteNode(currentDig);
				break;
			case '?':
				if (Exists(RootNode, currentDig) == 0)
					printf("\n%d no ", currentDig);
				else
					printf("\n%d yes ", currentDig);
				break;
			default:
				printf("Unknown operation!");
				break;
		}
		getchar();
	}
	printf("\n");
	PrintTree(RootNode);
}

void PrintTree(TreeItem node)
{
	if (node == NULL) return;
	
	PrintTree(node -> LNode);
	printf(" %d ", node -> NValue);
	PrintTree(node -> RNode);
	
}

short Exists(TreeItem node, int searchItem)
{
	if (node != NULL && node -> NValue == searchItem)
		return 1;
	if (node == NULL)
		return 0;
	
	if (node -> NValue > searchItem)
		return Exists(node -> LNode, searchItem);
	
	return Exists(node -> RNode, searchItem);
}

void AddNode(int currentVal)
{
	TreeItem newNode, currentNode;
	newNode = (Node*)malloc(sizeof(Node));
	newNode -> NValue = currentVal;
	newNode -> LNode = NULL;
	newNode -> RNode = NULL;
	
	if (RootNode == NULL)
	{
		RootNode = newNode;
		return;
	}

	currentNode = RootNode;
	while(1 == 1)
	{
		if (currentNode -> NValue > currentVal)
		{
			if (currentNode -> LNode != NULL)
			{
				currentNode = currentNode -> LNode;
				continue;
			}
			currentNode -> LNode = newNode;
			break;
		}
		if (currentNode -> NValue < currentVal)
		{
			if (currentNode -> RNode != NULL)
			{
				currentNode = currentNode -> RNode;
				continue;
			}
			currentNode -> RNode = newNode;
			break;
		}
		else
			return;
	}
}

void DeleteNode(int currentVal)
{
	if (RootNode == NULL) return;
	if (RootNode -> NValue == currentVal && 
	    RootNode -> LNode == NULL &&
	    RootNode -> RNode == NULL)
	{
		free(RootNode);
		RootNode = NULL;
		return;
	}
	
	TreeItem currentNode, deleteNode, previousNode, previousDeleteNode;
	currentNode = RootNode;
	while(1 == 1)
	{
		if (currentVal == currentNode -> NValue)
		{
			deleteNode = currentNode;
			if (currentNode == RootNode &&
			   (currentNode -> LNode == NULL ||
			    currentNode -> RNode == NULL))
			{
				RootNode = currentNode -> RNode == NULL ?
					currentNode -> LNode :
					currentNode -> RNode;
				free(deleteNode);
				break;
			}
			if (currentNode -> LNode == NULL &&
			    currentNode -> RNode == NULL)
			{
			    if (previousDeleteNode -> LNode == deleteNode)
					previousDeleteNode -> LNode = NULL;
				else
					previousDeleteNode ->RNode = NULL;
			    free(deleteNode);
			    break;
			}
			if (currentNode -> LNode != NULL &&
			    currentNode -> RNode == NULL)
			{
				currentNode = currentNode -> LNode;
				currentNode -> RNode =  deleteNode -> RNode;
			}
			else
			{
				while(currentNode -> RNode != NULL)
				{
					previousNode = currentNode;
					currentNode = currentNode -> RNode;
				}
				previousNode -> RNode = currentNode -> LNode;
				currentNode -> RNode = deleteNode -> RNode;
				currentNode -> LNode = deleteNode -> LNode;
			}
			if (deleteNode == RootNode)
				RootNode = currentNode;
			else
			{
				if (previousDeleteNode -> NValue < currentVal)
					previousDeleteNode -> RNode = currentNode;
				else
					previousDeleteNode -> LNode = currentNode;
			}
			free(deleteNode);
			break;
		}
		else
		{
			previousDeleteNode = currentNode;
			currentNode = currentVal < currentNode -> NValue ? 
					currentNode -> LNode : currentNode -> RNode;
		}
	}
}