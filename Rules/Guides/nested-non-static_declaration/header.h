/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:28:22 by dgerhard          #+#    #+#             */
/*   Updated: 2024/12/13 15:09:24 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_mem_tracker
{
	void	**addresses;
	size_t	capacity;
}					t_mem_tracker;

typedef struct s_data
{
	t_mem_tracker	trkr;
}				t_data;

void	init_mem_tracker(t_mem_tracker *trkr);
void	*ft_malloc(t_mem_tracker *trkr, size_t size);
void	add_address(t_mem_tracker *trkr, void *address);
void	free_trkr(t_mem_tracker *trkr);

void	ft_example(t_data *data);

#endif