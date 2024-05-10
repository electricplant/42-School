#include "reqs.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_formats(va_list args, const char format)
{
	int	printLen;

	printLen = 0;
	if (format == 'c')
		printLen += ft_printchar(va_arg(args, int));
	else if (format == 's')
		printLen += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		printLen += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		printLen += ft_printnumber(va_arg(args, int));
	else if (format == 'u')
		printLen += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		printLen += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		printLen += ft_print_perc();
	return (printLen);
}

int ft_printf(const char *str, ...)
{
	int i;
	int	printLen;
	va_list	args;

	i = 0;
	printLen = 0;
	va_start(args, str);
	
	while (str[i])
	{
		if (str[i] == '%')
		{
			printLen += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			printLen += ft_printchar(str[i]);
		i++;
	}
	
	va_end(args);
	return(printLen);
}
