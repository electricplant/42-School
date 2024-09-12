/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:21:07 by dgerhard          #+#    #+#             */
/*   Updated: 2024/09/12 16:28:00 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include "../ft_printf/include/libft.h"
# include "../ft_printf/include/reqs.h"

//MAIN
int		main(int argc, char **argv);
int		check_input(int argc, char **argv, long *a, long *b);
void	fill_stacks(int argc, char **argv, long *a, long *sizes);
void	print_stacks(long *a, long *b, int len);
void	is_sorted(long *a, long *sizes);

//FT_ERROR
int		ft_error(char *str);

//FILE 2
void	check_duplicates(int argc, long *a);
void	exit_free(long *a, long *b, long *sizes);
void	parameters(long *a, long *b, long *sizes);
void	rotate_a_twice(long *a, long *sizes);
void	reverot_a_twice(long *a, long *sizes);

//OPERATIONS_1
void	op_swap(long *x, char *msg, long *sizes);
void	op_ss(long *a, long *b, long *sizes);
void	op_pa(long *x, long *z, long *sizes);
void	op_pb(long *x, long *z, long *sizes);
void	op_rotate(long *x, char *msg, long *sizes);

//OPERATIONS_2
void	op_rr(long *a, long *b, long *sizes);
void	op_revrot(long *x, char *msg, long *sizes);
void	op_rrr(long *a, long *b, long *sizes);

//SMALL_CASES
void	small_cases(long *a, long *b, long *sizes);
void	sort_three(long *a, long *sizes);
void	sort_five(long *a, long *b, long *sizes);
void	first_stack(long *a, long *b, long *sizes);
void	second_stack(long *a, long *b, long *sizes);

//THE_MEAT
void	radix_sort(long *a, long *b, long *sizes);
void	shell_sort(long	*a, long *b, long *sizes);
long	get_max(long *a, long *sizes);
void	swap_these_two(long *a, long *b, long *sizes);

//MEAT_UTILS
void	scroll_pop(long *a, long *b, long *sizes, long i);
void scroll_swap(long *a, long *b, long *sizes)
#endif