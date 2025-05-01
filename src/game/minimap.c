/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:19:22 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/30 03:14:58 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	pos_x;
	int	pos_y;

	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			pos_x = x + j;
			pos_y = y + i;
			if (pos_x >= 0 && pos_x < game->win_w
				&& pos_y >= 0 && pos_y < game->win_h)
				game->frame.data[pos_y * game->win_w + pos_x] = color;
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (game->map.grid && game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			color = -1;
			if (game->map.grid[y][x] == '1')
				color = 0xFFFFFF;
			else if (game->map.grid[y][x] == '0')
				color = 0x000000;
			if (color != -1)
				draw_square(game, 10 + x * 5, 10 + y
					* 5, color);
			x++;
		}
		y++;
	}
	draw_square(game, 10 + (int)(game->player.pos_x * 5),
		10 + (int)(game->player.pos_y * 5), 0xFF0000);
}
