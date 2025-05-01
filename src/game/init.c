/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:29:32 by rgrochow          #+#    #+#             */
/*   Updated: 2025/05/01 14:18:04 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	tex->data = (int *)mlx_get_data_addr(tex->img, &game->bpp,
			&game->sl, &game->endian);
}

void	init_game(t_game *game)
{
	int	i;

	game->mlx = mlx_init();
	game->win_w = 640;
	game->win_h = 480;
	mlx_get_screen_size(game->mlx, &game->win_w, &game->win_h);
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "cub3D");
	i = 0;
	while (i < 70000)
		game->keys[i++] = 0;
	game->pitch = 0;
	game->ignore_mouse = 1;
	load_texture(game, &game->textures[0], game->textures[0].path);
	load_texture(game, &game->textures[1], game->textures[1].path);
	load_texture(game, &game->textures[2], game->textures[2].path);
	load_texture(game, &game->textures[3], game->textures[3].path);
	game->frame.img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	game->frame.data = (int *)mlx_get_data_addr(game->frame.img,
			&game->bpp, &game->sl, &game->endian);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.grid[ray->map_y][ray->map_x] != '0')
			ray->hit = 1;
	}
}

void	init_ray_direction(t_game *game, t_ray *ray, int x)
{
	ray->camera = 2 * x / (double)game->win_w - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	ray->side = 0;
}

void	init_ray_steps(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x
			= (game->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x
			= (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y
			= (game->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y
			= (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_dist_y;
	}
}
