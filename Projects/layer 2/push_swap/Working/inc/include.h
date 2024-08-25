/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:21:07 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/25 14:24:50 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "../ft_printf/include/libft.h"
# include "../ft_printf/include/reqs.h"

//MAIN
int		main(int argc, char **argv);
void	check_input(int argc, char **argv);
void	fill_stack(int argc, char **argv, char *a);
void	print_stacks(char *a, char *b);

//FT_ERROR
int	ft_error(char *str);

//FILE 2
void	check_duplicates(int argc, char *a);

//OPERATIONS_1
void	op_swap(char *stack, char *msg);
void	op_ss(char *a, char *b);
void	op_push(char *x, char *z, char *msg);
void	op_rotate(char *stack, char *msg);
#endif