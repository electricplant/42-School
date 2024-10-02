// Assignment name  : ft_swap
// Expected files   : ft_swap.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Write a function that swaps the contents of two integers the adresses of which
// are passed as parameters.

// Your function must be declared as follows:

// void	ft_swap(int *a, int *b);
#include <stdio.h>

void	ft_swap(int *a, int *b)
{
	int	x = *a;
	*a = *b;
	*b = x;
}

int	main(void)
{
	int	a = 10;
	int b = 22;

	printf("A:%d - B:%d\n", a, b);
	ft_swap(&a, &b);
	printf("A:%d - B:%d\n", a, b);
}