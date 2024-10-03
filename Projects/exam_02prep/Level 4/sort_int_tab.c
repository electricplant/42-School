// Assignment name  : sort_int_tab
// Expected files   : sort_int_tab.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Write the following function:

// void sort_int_tab(int *tab, unsigned int size);

// It must sort (in-place) the 'tab' int array, that contains exactly 'size'
// members, in ascending order.

// Doubles must be preserved.

// Input is always coherent.
#include <stdio.h>
#include <unistd.h>

void	sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	i = 0;
	int	temp;

	while (i < (size - 1))
	{
		if (tab[i] > tab[i + 1])
		{
			temp = tab[i];
			tab[i] = tab[i+ 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

int	main(int argc, char **argv)
{
	int i = 0;
	int	tab[] = {1, 9, 2, 4, 6, 5};
	while (i < 6)
	{
		printf("%d, ", tab[i]);
		i++;
	}
	printf("\n");
	i = 0;
	sort_int_tab(tab, 6);
	while (i < 6)
	{
		printf("%d, ", tab[i]);
		i++;
	}
	printf("\n");
}