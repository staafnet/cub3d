/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:51:41 by rgrochow          #+#    #+#             */
/*   Updated: 2025/05/01 15:33:31 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct s_ray
{
	double	camera;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		tex_x;
	double	wall_x;
	double	tex_pos;
	double	step;
}	t_ray;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_path
{
	int	ex;
	int	front;
	int	rear;
	int	x;
	int	y;
}	t_path;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	char	*path;
}	t_img;

typedef struct s_player
{
	double	move_speed;
	double	rot_speed;
	char	dir;
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	int			bpp;
	int			sl;
	int			endian;
	int			floor_color;
	int			ceiling_color;
	int			keys[70000];
	int			pitch;
	int			ignore_mouse;
	t_img		textures[4];
	t_img		frame;
	t_map		map;
	t_player	player;
	t_path		path;
}	t_game;

/* ************************************************************************** */
/*                                      FILE                                  */
/* ************************************************************************** */

/* check.c */
void	check_file(char *map_file);
/* init.c */
void	init_imgs(t_game *game, char *map_file);
/* utils.c */
int		count_lines(const char *map_file);
char	*read_line(int fd);

/* ************************************************************************** */
/*                                      MAP                                   */
/* ************************************************************************** */
/* init.c */
void	init_map(t_game *game, char *map_file);
/* check.c */
void	check_map(t_game *game);
/* utils.c */
int		bfs(t_game *game, int **directions, int **visited);

/* ************************************************************************** */
/*                                     PLAYER                                 */
/* ************************************************************************** */
/* check.c */
int		check_player(t_game *game, char *line, int height);
/* init.c */
void	init_player(t_game *game);

/* ************************************************************************** */
/*                                      GAME                                  */
/* ************************************************************************** */
/* init.c */
void	init_game(t_game *game);
void	init_ray_direction(t_game *game, t_ray *ray, int x);
void	init_ray_steps(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
/* events.c */
int		mouse_move(int x, int y, t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(void *game);
/* render.c */
void	render(t_game *game);
/* loop.c */
int		loop_hook(t_game *game);
/* minimap.c */
void	draw_minimap(t_game *game);
/* clear.c */
void	clear_game(t_game *game);
/* utils.c */
void	calculate_wall_distance(t_game *game, t_ray *ray);
void	choose_texture_number(t_ray *ray);
void	calculate_texture_coordinates(t_game *game, t_ray *ray);
int		get_wall_texture_color(t_game *game, t_ray *ray);
void	draw_vertical_line(t_game *game, t_ray *ray, int x);
/* ************************************************************************** */
/*                                     UTILS                                  */
/* ************************************************************************** */
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
