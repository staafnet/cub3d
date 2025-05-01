/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:04:34 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/30 03:22:04 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_player(t_game *game, char *line, int height)
{
	int	i;	

	i = 0;
	while (i < game->map.width - 1)
	{
		if (game->player.dir == 'X' && (line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'))
		{
			game->player.dir = line[i];
			game->player.pos_y = height + 0.5;
			game->player.pos_x = i + 0.5;
			game->map.grid[height][i] = '0';
		}
		else if (game->player.dir != 'X' && (line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'))
			return (0);
		i++;
	}
	return (1);
}
