/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_use.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:35:55 by dgerhard          #+#    #+#             */
/*   Updated: 2024/12/09 11:49:22 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_example(t_mem_tracker *tracker)
{
	ft_malloc(tracker, 41);
	ft_malloc(tracker, 51);
	ft_malloc(tracker, 61);
}
