// Assignment name  : max
// Expected files   : max.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Write the following function:

// int		max(int* tab, unsigned int len);

// The first parameter is an array of int, the second is the number of elements in
// the array.

// The function returns the largest number found in the array.

// If the array is empty, the function returns 0.
#include <stdio.h>

int	max(int *tab, unsigned int len)
{
	int	i;
	int	x;
	int	k;

	i = 0;
	x = 0;
	k = 0;
	if (len == 0)
		return (0);
	while (i < len)
	{
		k = i;
		x = tab[i];
		while (k >= 0)
		{
			if (x < tab[k])
				x = tab[k];
			k--;
		}
		i++;
	}
	return (x);
	
}

int	main(void)
{
	int	tab[] = {11, 2, 4, 9, 2, 10, 8};
	printf("Returned: %d\n", max(tab, 6));
}
