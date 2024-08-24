/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:21:07 by dgerhard          #+#    #+#             */
/*   Updated: 2024/08/24 10:33:35 by dgerhard         ###   ########.fr       */
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
//void	check_duplicates(int argc, char **argv);

//FT_ERROR
int	ft_error(char *str);

#endif