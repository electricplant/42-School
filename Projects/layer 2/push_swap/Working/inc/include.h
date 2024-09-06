/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:21:07 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/06 12:36:05 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "../ft_printf/include/libft.h"
# include "../ft_printf/include/reqs.h"

//MAIN
int		main(int argc, char **argv);
int		check_input(int argc, char **argv, int *a, int *b, int *sizes);
void	fill_stacks(int argc, char **argv, int *a, int *sizes);
void	print_stacks(int *a, int *b, int len);
void	is_sorted(int *a, int *sizes)

//FT_ERROR
int		ft_error(char *str);

//FILE 2
void	check_duplicates(int argc, int *a);
void	exit_free(int *a, int *b, int *sizes);

//OPERATIONS_1
void	op_swap(int *x, char *msg, int *sizes);
void	op_ss(int *a, int *b, int *sizes);
void	op_pa(int *x, int *z, int *sizes);
void	op_pb(int *x, int *z, int *sizes);
void	op_rotate(int *x, char *msg, int *sizes);

//OPERATIONS_2
void	op_rr(int *a, int *b, int *sizes);
void	op_revrot(int *x, char *msg, int *sizes);
void	op_rrr(int *a, int *b, int *sizes);
#endif