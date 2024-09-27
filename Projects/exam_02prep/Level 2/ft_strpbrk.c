// Assignment name	: ft_strpbrk
// Expected files	: ft_strpbrk.c
// Allowed functions: None
// ---------------------------------------------------------------

// Reproduce exactly the behavior of the function strpbrk
// (man strpbrk).

// The function should be prototyped as follows:

// char	*ft_strpbrk(const char *s1, const char *s2);

#include <string.h>
#include <stdio.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	const char	*p;
	while (*s1)
	{
		p = s2;
		while (*p)
		{
			if (*s1 == *p)
				return (char *)s1;
			p++;
		}
		s1++;
	}
	return (NULL);
}

int	main(void)
{
	char	*s1 = "helloba";
	char	*s2 = "abco";
	char	*point;

	point = ft_strpbrk(s1, s2);
	printf("%s\n", point);
}