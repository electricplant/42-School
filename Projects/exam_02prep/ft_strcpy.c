// Assignment name  : ft_strcpy
// Expected files   : ft_strcpy.c
// Allowed functions:
// --------------------------------------------------------------------------------

// Reproduce the behavior of the function strcpy (man strcpy).

// Your function must be declared as follows:

// char    *ft_strcpy(char *s1, char *s2);
#include <stdio.h>
#include <stdlib.h>

char	*ft_strcpy(char *s1, char *s2)
{
	int	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = 0;
}

int	main(void)
{
	char	*s1;
	char	*s2 = "hello";

	s1 = (char *)malloc(5 * sizeof(char));
	ft_strcpy(s1, s2);
	printf("%s", s1);

	free(s1);
}