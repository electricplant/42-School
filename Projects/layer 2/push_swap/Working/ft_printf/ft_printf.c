/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:24:04 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/02 12:24:04 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reqs.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_formats(va_list args, const char format)
{
	int	plen;

	plen = 0;
	if (format == 'c')
		plen += ft_printchar(va_arg(args, int));
	else if (format == 's')
		plen += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		plen += ft_print_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		plen += ft_printnumber(va_arg(args, int));
	else if (format == 'u')
		plen += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		plen += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		plen += ft_print_perc();
	return (plen);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		plen;
	va_list	args;

	i = 0;
	plen = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			plen += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			plen += ft_printchar(str[i]);
		i++;
	}
	va_end (args);
	return (plen);
}
