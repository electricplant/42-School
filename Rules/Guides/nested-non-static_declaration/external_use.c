/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_use.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:35:55 by dgerhard          #+#    #+#             */
/*   Updated: 2024/12/09 11:43:58 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_example(t_data *data)
{
	ft_malloc(&data->tracker, 40);
	ft_malloc(&data->tracker, 50);
	ft_malloc(&data->tracker, 60);
}