// Assignment name  : ft_strcmp
// Expected files   : ft_strcmp.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Reproduce the behavior of the function strcmp (man strcmp).

// Your function must be declared as follows:

// int    ft_strcmp(char *s1, char *s2);
#include <stdio.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while((s1 != 0) && (s2 != 0) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);

}

int	main(void)
{
	char	*s1 = "hello";
	char	*s2 = "hillo";
	int		ret = 0;

	ret = ft_strcmp(s1, s2);
	printf("%d\n", ret);
}