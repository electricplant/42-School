// Assignment name  : ft_strrev
// Expected files   : ft_strrev.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Write a function that reverses (in-place) a string.

// It must return its parameter.

// Your function must be declared as follows:

// char    *ft_strrev(char *str);
#include <stdio.h>

char	*ft_strrev(char *str)
{
	char	swap;
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (str[len])
		len++;
	while (++i < (len / 2))
	{
		swap = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = swap;
	}
	return (str);
}

int	main(void)
{
	char str[] = "hello";

	ft_strrev(str);
	printf("%s\n", str);

}
