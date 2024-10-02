// Assignment name  : ft_atoi_base
// Expected files   : ft_atoi_base.c
// Allowed functions: None
// --------------------------------------------------------------------------------

// Write a function that converts the string argument str (base N <= 16)
// to an integer (base 10) and returns it.

// The characters recognized in the input are: 0123456789abcdef
// Those are, of course, to be trimmed according to the requested base. For
// example, base 4 recognizes "0123" and base 16 recognizes "0123456789abcdef".

// Uppercase letters must also be recognized: "12fdb3" is the same as "12FDB3".

// Minus signs ('-') are interpreted only if they are the first character of the
// string.
#include <stdio.h>

char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	get_digit(char c, int digit_base)
{
	int	max_digit = 0;

	if (digit_base <= 10)
		max_digit = digit_base - 1 + '0';
	else
		max_digit = digit_base - 10 - 1 + 'a';
	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);

}

int	ft_atoi_base(const char *str, int str_base)
{
	int	result = 0;
	int	sign = 1;
	int	number = 0;

	if (str == NULL || str_base < 2 || str_base > 16)
		return (0);
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	while (*str)
	{
		number = get_digit(to_lower(*str), str_base);
		if (number == -1)
			break;
		result = result * str_base + number;
		++str;
	}
	return (result * sign);
}

int	main(void)
{
	printf("%d\n", ft_atoi_base("1000101", 2));
}