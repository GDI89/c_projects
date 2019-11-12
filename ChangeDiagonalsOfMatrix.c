// Function (void type) that swaps the main and side diagonals matrices of integers (int type) 
// of size NxN, where N is specified using the define directive constant.

#include <stdio.h>

#define N 5
void ChangeDiagonals(int currentMatrix[N][N]);

int main(void) {
	int i,j;
	int matrix[N][N] = {{-1,  1,  1,  1,  1},
		        { 9, -2,  2,  1,  1},
		        { 0,  8, -3,  3,  1},
		        { 0,  0,  7, -4,  4},
		        { 0,  0,  0,  6, -5}};
	ChangeDiagonals(matrix);
	for ( i = 0; i < N; i++) 
	{
	    for ( j = 0; j < N; j++) 
	    {
	        printf("%4d", matrix[i][j]);
	    }
	    printf("\n");
	}
	printf("\n");
	return 0;
}

void ChangeDiagonals(int currentMatrix[N][N])
{
	int i,j;
	for (i=0; i<N; i++) 
	{
	    for (j=0; j<N; j++)
	    {
	        if (i == j) 
	        {
	            int temp = currentMatrix[i][j];
	            currentMatrix[i][j] = currentMatrix[i][N-j-1];
	            currentMatrix[i][N-j-1] = temp;
	        }
	    }
	}	
}