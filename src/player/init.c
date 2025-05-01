/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:04:52 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/30 03:24:19 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_direction(t_game *game)
{
	if (game->player.dir == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
	}
	else if (game->player.dir == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
	}
	else if (game->player.dir == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
	}
	else if (game->player.dir == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
	}
}

static void	init_plane(t_game *game)
{
	if (game->player.dir == 'N')
	{
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	else if (game->player.dir == 'S')
	{
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
	else if (game->player.dir == 'E')
	{
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	else if (game->player.dir == 'W')
	{
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
}

void	init_player(t_game *game)
{
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.05;
	init_direction(game);
	init_plane(game);
}
