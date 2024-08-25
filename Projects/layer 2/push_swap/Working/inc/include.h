/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:21:07 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/25 19:44:19 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "../ft_printf/include/libft.h"
# include "../ft_printf/include/reqs.h"

//MAIN
int		main(int argc, char **argv);
void	check_input(int argc, char **argv);
void	fill_stacks(int argc, char **argv, int *a, int **b);
void	print_stacks(int *a, int *b, int len);

//FT_ERROR
int	ft_error(char *str);

//FILE 2
void	check_duplicates(int argc, int *a);

//OPERATIONS_1
void	op_swap(int *stack, char *msg);
void	op_ss(char *a, char *b);
void	op_push(int **x, int **z, char *msg);
void	op_rotate(char *stack, char *msg);

//OPERATIONS_2
void	rr(char *a, char *b);
void	op_rrr(char *stack, char *msg);
void	rrr(char *a, char *b);
#endif