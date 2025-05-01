/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:33:00 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/29 22:28:24 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_color(int *color, char *line)
{
	int		r;
	int		g;
	int		b;
	char	*ptr;

	r = 0;
	g = 0;
	b = 0;
	ptr = line;
	while (*ptr == ' ' || *ptr == ',')
		ptr++;
	while (*ptr >= '0' && *ptr <= '9')
		r = r * 10 + (*ptr++ - '0');
	while (*ptr == ' ' || *ptr == ',')
		ptr++;
	while (*ptr >= '0' && *ptr <= '9')
		g = g * 10 + (*ptr++ - '0');
	while (*ptr == ' ' || *ptr == ',')
		ptr++;
	while (*ptr >= '0' && *ptr <= '9')
		b = b * 10 + (*ptr++ - '0');
	*color = (r << 16) | (g << 8) | b;
}

static void	init_line(t_game *game, char *line, int i)
{
	if (i == 0)
		game->textures[0].path = ft_strdup(line + 3);
	else if (i == 1)
		game->textures[1].path = ft_strdup(line + 3);
	else if (i == 2)
		game->textures[2].path = ft_strdup(line + 3);
	else if (i == 3)
		game->textures[3].path = ft_strdup(line + 3);
	else if (i == 5)
		init_color(&game->floor_color, line + 2);
	else if (i == 6)
		init_color(&game->ceiling_color, line + 2);
}

static int	file_exists(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	init_imgs(t_game *game, char *map_file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_file, O_RDONLY);
	i = 0;
	while (i < 7)
	{
		line = read_line(fd);
		init_line(game, line, i);
		free(line);
		i++;
	}
	close(fd);
	if (!file_exists(game->textures[0].path)
		|| !file_exists(game->textures[1].path)
		|| !file_exists(game->textures[2].path)
		|| !file_exists(game->textures[3].path))
		(free(game->textures[0].path), free(game->textures[1].path),
			free(game->textures[2].path), free(game->textures[3].path),
			printf("Texture error\n"), exit(0));
}
