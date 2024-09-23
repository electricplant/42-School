#include "reqs.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_formats(va_list args, const char format)
{
	int	printlenth;

	printlenth = 0;
	if (format == 'c')
		printlenth += ft_printchar(va_arg(args, int));
	else if (format == 's')
		printlenth += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		printlenth += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		printlenth += ft_printnumber(va_arg(args, int));
	else if (format == 'u')
		printlenth += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		printlenth += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		printlenth += ft_print_perc(void);
	return (printlenth);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	int			printlenth;
	va_list		args;

	i = 0;
	printlenth = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			printlenth += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			printlenth += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (printlenth);
}
