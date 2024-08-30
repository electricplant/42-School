/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:21:07 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/29 10:16:32 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "../ft_printf/include/libft.h"
# include "../ft_printf/include/reqs.h"

//MAIN
int		main(int argc, char **argv);
void	check_input(int argc, char **argv);
void	fill_stacks(int argc, char **argv, int *a, int *b, int *sizes);
void	print_stacks(int *a, int *b, int len);

//FT_ERROR
int	ft_error(char *str);

//FILE 2
void	check_duplicates(int argc, int *a);

//OPERATIONS_1
void	op_swap(int *x, char *msg, int *sizes);
void	op_ss(int *a, int *b, int *sizes);
void	op_pa(int *x, int *z, int *sizes);
void	op_rotate(char *stack, char *msg);

//OPERATIONS_2
void	rr(char *a, char *b);
void	op_rrr(char *stack, char *msg);
void	rrr(char *a, char *b);
#endif