/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reqs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:13:38 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/23 14:13:38 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQS_H
# define REQS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int		ft_printf(const char *str, ...);
int		ft_printchar(char c);
int		ft_printstr(char *s);
int		ft_formats(va_list args, const char format);
int		ft_printnumber(int n);
int		ft_print_perc(void);
int		ft_print_ptr(unsigned long long ptr);
int		ft_print_hex(unsigned int num, const char format);
int		ft_hex_len(unsigned	int num);
int		ft_num_len(unsigned	int num);
int		ft_print_unsigned(unsigned int n);

void	ft_putstr(char *str);
void	ft_put_hex(unsigned int num, const char format);

char	*ft_uitoa(unsigned int n);

#endif