/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_use.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:35:55 by dgerhard          #+#    #+#             */
/*   Updated: 2024/12/13 13:02:13 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_example(t_data *data)
{
	ft_malloc(&data->trkr, 40);
	ft_malloc(&data->trkr, 50);
	ft_malloc(&data->trkr, 60);
}