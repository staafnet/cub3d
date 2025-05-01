/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:52:47 by rgrochow          #+#    #+#             */
/*   Updated: 2025/05/01 14:59:55 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(t_game *game)
{
	t_ray	ray;
	int		i;

	i = 0;
	while (i < game->win_w)
	{
		init_ray_direction(game, &ray, i);
		init_ray_steps(game, &ray);
		perform_dda(game, &ray);
		calculate_wall_distance(game, &ray);
		choose_texture_number(&ray);
		calculate_texture_coordinates(game, &ray);
		draw_vertical_line(game, &ray, i);
		i++;
	}
}
