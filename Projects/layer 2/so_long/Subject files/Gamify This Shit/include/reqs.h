/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerhard <dgerhard@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:34:38 by dgerhard          #+#    #+#             */
/*   Updated: 2024/05/17 16:34:41 by dgerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQS_H
# define REQS_H

# include "structs.h"
# include <stdio.h>
# include <stdlib.h>
# include "../../../Working/minilibx-linux/mlx.h"
# include <X11/X.h>
# include "get_next_line.h"

# include <unistd.h> //remove later

int		close_window(t_data *img);
void	move_player(t_data *img);
int		key_hook(int keycode, t_data *img);
int		ft_get_map(char *file, t_map *map);


#endif