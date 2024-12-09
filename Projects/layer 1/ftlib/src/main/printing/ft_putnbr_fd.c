/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:57:22 by dgerhard          #+#    #+#             */
/*   Updated: 2023/09/06 17:04:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_nb(long nb, int fd)
{
	if (nb / 10)
	{
		print_nb(nb / 10, fd);
		print_nb(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	print_nb(nb, fd);
}
