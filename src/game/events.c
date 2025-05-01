/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:29:30 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/30 03:32:23 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	handle_rotation(t_game *game, int delta_x, int delta_y)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	rot = delta_x * game->player.rot_speed * 0.008;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot)
		- game->player.dir_y * sin(rot);
	game->player.dir_y = old_dir_x * sin(rot) + game->player.dir_y * cos(rot);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot)
		- game->player.plane_y * sin(rot);
	game->player.plane_y = old_plane_x * sin(rot)
		+ game->player.plane_y * cos(rot);
	game->pitch -= delta_y * 0.5;
	if (game->pitch > game->win_h / 2)
		game->pitch = game->win_h / 2;
	else if (game->pitch < -game->win_h / 2)
		game->pitch = -game->win_h / 2;
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	center_x;
	static int	center_y;
	int			delta_x;
	int			delta_y;

	if (center_x == 0 || center_y == 0)
	{
		center_x = game->win_w / 2;
		center_y = game->win_h / 2;
		mlx_mouse_move(game->mlx, game->win, center_x, center_y);
		return (0);
	}
	delta_x = x - center_x;
	delta_y = y - center_y;
	handle_rotation(game, delta_x, delta_y);
	mlx_mouse_move(game->mlx, game->win, center_x, center_y);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 70000)
		game->keys[keycode] = 1;
	if (keycode == 65307)
		(clear_game(game), exit(0));
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 70000)
		game->keys[keycode] = 0;
	return (0);
}

int	close_window(void *game)
{
	clear_game(game);
	exit(0);
	return (0);
}
