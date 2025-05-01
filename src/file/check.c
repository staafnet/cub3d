/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:10:24 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/21 16:04:43 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_color_format(char *ptr)
{
	int	comma;

	comma = 0;
	while (*ptr)
	{
		if (*ptr == ',')
		{
			comma++;
			if (!*(ptr - 1) || !*(ptr + 1))
				return (0);
			if ((*(ptr - 1) < '0' || *(ptr - 1) > '9')
				|| (*(ptr + 1) < '0' || *(ptr + 1) > '9'))
				return (0);
		}
		if ((*ptr >= '0' && *ptr <= '9') || *ptr == ',')
			ptr++;
		else
			return (0);
	}
	return (comma == 2);
}

static int	check_color(char *line)
{
	int		r;
	int		g;
	int		b;
	char	*ptr;

	r = 0;
	g = 0;
	b = 0;
	ptr = line + 2;
	if (!is_valid_color_format(ptr))
		return (0);
	while (*ptr >= '0' && *ptr <= '9')
		r = r * 10 + (*ptr++ - '0');
	ptr++;
	while (*ptr >= '0' && *ptr <= '9')
		g = g * 10 + (*ptr++ - '0');
	ptr++;
	while (*ptr >= '0' && *ptr <= '9')
		b = b * 10 + (*ptr++ - '0');
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (0);
	return (1);
}

static int	check_line(char *line, int i)
{
	if ((ft_strncmp(line, "NO ", 3) != 0 && i == 0)
		|| (ft_strncmp(line, "SO ", 3) != 0 && i == 1)
		|| (ft_strncmp(line, "WE ", 3) != 0 && i == 2)
		|| (ft_strncmp(line, "EA ", 3) != 0 && i == 3)
		|| (ft_strcmp(line, "") != 0 && i == 4)
		|| (ft_strncmp(line, "F ", 2) != 0 && i == 5)
		|| (ft_strncmp(line, "C ", 2) != 0 && i == 6)
		|| (ft_strcmp(line, "") != 0 && i == 7))
		return (0);
	else if (i > 7)
	{
		while (*line)
		{
			if (*line == ' ' || *line == '\n' || *line == '0' || *line == '1'
				|| *line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			{
				line++;
				continue ;
			}
			else
				return (0);
		}
	}
	return (1);
}

static int	check_lines(int lines, char *map_file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(map_file, O_RDONLY);
	i = 0;
	while (i < lines)
	{
		line = read_line(fd);
		if (!line)
		{
			i++;
			continue ;
		}
		if (!check_line(line, i))
			return (close(fd), free(line), 0);
		if (i == 5 || i == 6)
			if (!check_color(line))
				return (close(fd), free(line), 0);
		(free(line), i++);
	}
	return (close(fd), 1);
}

void	check_file(char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		(printf("File not found: %s\n", map_file), exit(0));
	close(fd);
	if (count_lines(map_file) < 11)
		(printf("Error map file\n"), exit(0));
	if (!check_lines(count_lines(map_file), (char *)map_file))
		(printf("Error map structure\n"), exit(0));
}
