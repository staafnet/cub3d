/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:54:15 by rgrochow          #+#    #+#             */
/*   Updated: 2025/05/01 15:14:58 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.pos_x
				+ (1 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.pos_y
				+ (1 - ray->step_y) / 2.0) / ray->ray_dir_y;
	ray->line_h = (int)(game->win_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_h / 2 + game->win_h / 2 + game->pitch;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + game->win_h / 2 + game->pitch;
	if (ray->draw_end >= game->win_h)
		ray->draw_end = game->win_h - 1;
}

void	choose_texture_number(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex_num = 2;
		else
			ray->tex_num = 3;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->tex_num = 1;
		else
			ray->tex_num = 0;
	}
}

void	calculate_texture_coordinates(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * game->textures[ray->tex_num].width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = game->textures[ray->tex_num].width - ray->tex_x - 1;
	ray->step = 1.0 * game->textures[ray->tex_num].height / ray->line_h;
	ray->tex_pos = (ray->draw_start - game->pitch - game->win_h
			/ 2 + ray->line_h / 2) * ray->step;
}

int	get_wall_texture_color(t_game *game, t_ray *ray)
{
	int	tex_y;
	int	color;

	tex_y = (int)ray->tex_pos;
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	if (ray->tex_x >= game->textures[ray->tex_num].width)
		ray->tex_x = game->textures[ray->tex_num].width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= game->textures[ray->tex_num].height)
		tex_y = game->textures[ray->tex_num].height - 1;
	color = game->textures[ray->tex_num].data[
		tex_y * game->textures[ray->tex_num].width + ray->tex_x];
	ray->tex_pos += ray->step;
	return (color);
}

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	int	color;
	int	i;

	i = 0;
	while (i < game->win_h)
	{
		if (i < ray->draw_start)
			color = game->ceiling_color;
		else if (i <= ray->draw_end)
			color = get_wall_texture_color(game, ray);
		else
			color = game->floor_color;
		if (i >= 0 && i < game->win_h)
			game->frame.data[i * game->win_w + x] = color;
		i++;
	}
}
