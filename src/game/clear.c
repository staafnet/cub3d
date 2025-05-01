/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:22:44 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/30 01:50:45 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clear_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.grid)
	{
		while (game->map.grid[i])
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		if (game->textures[i].path)
			free(game->textures[i].path);
		i++;
	}
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		(mlx_destroy_display(game->mlx), free(game->mlx));
}
