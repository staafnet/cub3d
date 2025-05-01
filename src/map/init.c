/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:39:05 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/29 22:42:13 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_line(t_game *game, char *line, int n)
{
	int	i;

	i = 0;
	game->map.grid[n] = malloc(sizeof(char) * (game->map.width + 1));
	if (!game->map.grid[n])
		return ;
	if (n == 0 || n == game->map.height - 2)
	{
		while (i < game->map.width)
			game->map.grid[n][i++] = ' ';
		game->map.grid[n][i++] = '\0';
		return ;
	}
	game->map.grid[n][0] = ' ';
	i = 1;
	while (i < game->map.width)
	{
		if (i > ft_strlen(line))
			game->map.grid[n][i] = ' ';
		else
			game->map.grid[n][i] = line[i - 1];
		i++;
	}
	game->map.grid[n][i] = '\0';
}

static void	init_width(t_game *game, char *map_file, int lines)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_file, O_RDONLY);
	i = 0;
	game->map.width = 0;
	while (i < lines)
	{
		line = read_line(fd);
		if (!line)
		{
			i++;
			continue ;
		}
		if (i > 7 && ft_strlen(line) > game->map.width)
			game->map.width = ft_strlen(line) + 2;
		(free(line), i++);
	}
	close(fd);
}

void	init_map(t_game *game, char *map_file)
{
	int		fd;
	int		i;
	char	*line;
	int		lines;

	lines = count_lines(map_file);
	init_width(game, map_file, lines);
	game->map.height = lines - 5;
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		(free(game->textures[0].path), free(game->textures[1].path),
			free(game->textures[2].path), free(game->textures[3].path),
			printf("Map error\n"), exit(0));
	fd = open(map_file, O_RDONLY);
	i = 0;
	while (i <= lines)
	{
		line = read_line(fd);
		if (i > 6)
			init_line(game, line, i - 7);
		free(line);
		i++;
	}
	game->map.grid[game->map.height - 1] = NULL;
	close(fd);
}
