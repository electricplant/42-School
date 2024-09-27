// Assignment name  : ft_strdup
// Expected files   : ft_strdup.c
// Allowed functions: malloc
// --------------------------------------------------------------------------------

// Reproduce the behavior of the function strdup (man strdup).

// Your function must be declared as follows:

// char    *ft_strdup(char *src);
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(char *src)
{
	int	i;
	char	*dst;

	i = 0;
	while (src[i])
		i++;
	dst = (char *)malloc((i + 1) * sizeof(src));
	i = 0;
	if (src != NULL)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}

int	main(void)
{
	char	*src;
	char	*dst;

	src = (char *)malloc(6 * sizeof(char));
	src = "hello";
	dst = ft_strdup(src);
	printf("input %s, output %s\n", src, dst);
}