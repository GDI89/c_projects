// The Calculator operates by the recursive descent method and is built on the basis of the following grammar (operations are left-associative):
// <expression> ::= <summand>{+|- <summand>}
// <summand>    ::= <multiplier>{*|/ <multiplier>}
// <multiplier> ::= 0|1|2|3|4|5|6|7|8|9|{^(<expression>)}

#include <stdio.h>
#include <setjmp.h>
#include <math.h>

jmp_buf begin;

char currentLexem;
void GetLexem(void); 
int Expression(void);
int GetSummand(void);
int GetMultiplier(void);
int Value(void);
void Error();

int main() 
{
	int result = 0;
	setjmp(begin);
	printf("==>");
	GetLexem();
	result = Expression();
	printf("\n%d\n",result);
	return 0;
}

void GetLexem() 
{
	while((currentLexem = getchar()) == ' ');
}

void Error(void)
{
	printf("\nОШИБКА!\n");
	while(getchar() != '\n');
	longjmp(begin, 1);
}

int Expression()
{
	int summand = GetSummand();
	while(currentLexem == '+' || currentLexem == '-')
	{
		char operationLex = currentLexem;
		GetLexem();
		switch(operationLex)
		{
			case '-':
				summand -= GetSummand();
				break;
			case '+':
				summand += GetSummand();
				break;
		}
	}
	return summand;
}

int GetSummand()
{
	int multiplier = GetMultiplier();
	while(currentLexem == '*' || currentLexem == '/')
	{
		char operationLex = currentLexem;
		GetLexem();
		switch(operationLex)
		{
			case '*':
				multiplier *= GetMultiplier();
				break;
			case '/':
				multiplier /= GetMultiplier();
				break;
		}
	}
	return multiplier;
}

int GetMultiplier()
{
	int currentValue = Value();
	if (currentLexem != '^') return currentValue;
	GetLexem();
	return  pow(currentValue, GetMultiplier());
}

int Value()
{
	int nextLexem;
	switch(currentLexem)
	{
		case'0': case'1': case'2': case'3': 
		case'4': case'5': case'6': case'7':
		case'8': case'9':
			nextLexem = currentLexem - '0';
			break;
		case'(':
			GetLexem();
			nextLexem = Expression();
			if(currentLexem == ')') break; 
		default: Error();
	} 
	GetLexem();
	return nextLexem;
}