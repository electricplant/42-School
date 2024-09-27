// Assignment name	: ft_strcspn
// Expected files	: ft_strcspn.c
// Allowed functions: None
// ---------------------------------------------------------------

// Reproduce exactly the behavior of the function strcspn
// (man strcspn).

// The function should be prototyped as follows:

// size_t	ft_strcspn(const char *s, const char *reject);
#include <string.h>
#include <stdio.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (reject[i])
	{
		while (s[j])
		{
			if (reject[i] == s[j])
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (i);
}

int	main(void)
{
	char	*s = "frick";
	char	*reject = "abcdefghi";
	size_t	ret = 0;

	ret = ft_strcspn(s, reject);
	printf("Returned: %ld\n", ret);
	return (0);
}
