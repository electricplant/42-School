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
	while(*s1 != '\0')
		*s2 = *s1++;
	return (s2);
}

int	main(void)
{
	char	*s1 = "hello";
	char	*s2;

	s2 = (char *)malloc(6 * sizeof(char));
	s2 = ft_strcpy(s2, s1);
	printf("Returned %s", s2);
}
