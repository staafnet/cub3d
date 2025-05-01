/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:34:09 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/30 03:46:42 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move_player(t_game *game, double *new_x, double *new_y)
{
	if (game->keys[122])
	{
		*new_x += game->player.dir_x * game->player.move_speed;
		*new_y += game->player.dir_y * game->player.move_speed;
	}
	if (game->keys[115])
	{
		*new_x -= game->player.dir_x * game->player.move_speed;
		*new_y -= game->player.dir_y * game->player.move_speed;
	}
	if (game->keys[113])
	{
		*new_x -= game->player.plane_x * game->player.move_speed;
		*new_y -= game->player.plane_y * game->player.move_speed;
	}
	if (game->keys[100])
	{
		*new_x += game->player.plane_x * game->player.move_speed;
		*new_y += game->player.plane_y * game->player.move_speed;
	}
}

static void	rotate_player(t_game *game)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	angle = 0.0;
	if (game->keys[65363])
		angle = game->player.rot_speed;
	else if (game->keys[65361])
		angle = -game->player.rot_speed;
	else
		return ;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

static void	apply_collision(t_game *game, double new_x, double new_y)
{
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] == '0')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] == '0')
		game->player.pos_y = new_y;
}

int	loop_hook(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x;
	new_y = game->player.pos_y;
	move_player(game, &new_x, &new_y);
	rotate_player(game);
	apply_collision(game, new_x, new_y);
	render(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
	game->ignore_mouse = 0;
	return (0);
}
