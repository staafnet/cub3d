/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:40:52 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/30 04:45:10 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	search_while(t_game *game, int **visited, int **q, int **directions)
{
	int	nx;
	int	ny;
	int	i;

	i = 0;
	while (i < 4)
	{
		nx = game->path.x + directions[i][0];
		ny = game->path.y + directions[i][1];
		if (nx >= 0 && nx < game->map.width && ny >= 0
			&& ny < game->map.height
			&& !visited[ny][nx] && game->map.grid[ny][nx] != '1')
		{
			visited[ny][nx] = 1;
			if (game->map.grid[ny][nx] == ' ')
			{
				game->path.ex = 0;
				return ;
			}
			game->path.rear++;
			q[game->path.rear][0] = nx;
			q[game->path.rear][1] = ny;
		}
		i++;
	}
}

static void	search(t_game *game, int **visited, int **q, int **directions)
{
	while (game->path.front <= game->path.rear)
	{
		game->path.x = q[game->path.front][0];
		game->path.y = q[game->path.front][1];
		game->path.front++;
		search_while(game, visited, q, directions);
	}
}

static int	**q_init(t_game *game)
{
	int	**q;
	int	i;

	q = malloc(game->map.width * game->map.height * sizeof(int *));
	if (!q)
		return (NULL);
	i = 0;
	while (i < game->map.width * game->map.height)
	{
		q[i] = malloc(2 * sizeof(int));
		if (!q[i])
		{
			while (--i >= 0)
				free(q[i]);
			free(q);
			return (NULL);
		}
		i++;
	}
	return (q);
}

static void	q_free(t_game *game, int **q)
{
	int	i;

	i = 0;
	while (i < game->map.width * game->map.height)
		free(q[i++]);
	free(q);
}

int	bfs(t_game *game, int **directions, int **visited)
{
	int		**q;

	game->path.front = 0;
	game->path.rear = 0;
	game->path.ex = 1;
	q = q_init(game);
	q[game->path.rear][0] = (int)game->player.pos_x;
	q[game->path.rear][1] = (int)game->player.pos_y;
	visited[(int)game->player.pos_y][(int)game->player.pos_x] = 1;
	search(game, visited, q, directions);
	q_free(game, q);
	return (game->path.ex);
}
