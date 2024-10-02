// Assignment name  : repeat_alpha
// Expected files   : repeat_alpha.c
// Allowed functions: write

// Write a program called repeat_alpha that takes a string and display it
// repeating each alphabetical character as many times as its alphabetical index,
// followed by a newline.

// 'a' becomes 'a', 'b' becomes 'bb', 'e' becomes 'eeeee', etc...

// Case remains unchanged.

// If the number of arguments is not 1, just display a newline.

// Examples:

// $>./repeat_alpha "abc"
// abbccc
// $>./repeat_alpha "Alex." | cat -e
// Alllllllllllleeeeexxxxxxxxxxxxxxxxxxxxxxxx.$
// $>./repeat_alpha 'abacadaba 42!' | cat -e
// abbacccaddddabba 42!$
// $>./repeat_alpha | cat -e
// $
// $>
// $>./repeat_alpha "" | cat -e
// $
// $>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while ((argc == 2) && argv[1][i])
	{
		j = 0;
		if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
		{
			while (j <= (argv[1][i] - 'A'))
			{
				write(1, &argv[1][i], 1);
				j++;
			}
		}
		else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
		{
			while (j <= (argv[1][i] - 'a'))
			{
				write(1, &argv[1][i], 1);
				j++;
			}
		}
		else
			write(1, &argv[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
}
