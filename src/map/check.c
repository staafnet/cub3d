/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:29:23 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/30 04:44:20 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	**init_visited(t_game *game)
{
	int	**visited;
	int	i;
	int	j;

	visited = malloc((game->map.height) * sizeof(int *));
	if (!visited)
		(clear_game(game), exit(0));
	i = 0;
	while (i < game->map.height)
	{
		visited[i] = malloc((game->map.width) * sizeof(int));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			(free(visited), clear_game(game), exit(0));
		}
		j = 0;
		while (j < game->map.width)
			visited[i][j++] = 0;
		i++;
	}
	return (visited);
}

static int	**init_directions(void)
{
	int			i;
	static int	directions[4][2];
	static int	*dir[4];

	directions[0][0] = 0;
	directions[0][1] = 1;
	directions[1][0] = 0;
	directions[1][1] = -1;
	directions[2][0] = 1;
	directions[2][1] = 0;
	directions[3][0] = -1;
	directions[3][1] = 0;
	i = 0;
	while (i < 4)
	{
		dir[i] = directions[i];
		i++;
	}
	return (dir);
}

static int	is_access(t_game *game)
{
	int	**directions;
	int	**visited;
	int	valid;
	int	i;

	valid = 0;
	directions = init_directions();
	visited = init_visited(game);
	printf("%d", directions[0][0]);
	if (bfs(game, directions, visited))
		valid = 1;
	i = 0;
	while (i < game->map.height)
		free(visited[i++]);
	free(visited);
	return (valid);
}

static void	clear(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.grid)
	{
		while (game->map.grid[i])
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	(free(game->textures[0].path), free(game->textures[1].path));
	(free(game->textures[2].path), free(game->textures[3].path));
}

void	check_map(t_game *game)
{
	int	i;

	game->player.dir = 'X';
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	i = 0;
	while (i < game->map.height - 1)
	{
		if (!check_player(game, game->map.grid[i], i))
			(printf("Player position error\n"),
				clear(game), exit(0));
		i++;
	}
	init_player(game);
	if (game->player.dir == 'X')
		(printf("Player position error\n"),
			clear(game), exit(0));
	if (!is_access(game))
		(clear(game), printf("Map error\n"), exit(0));
}
