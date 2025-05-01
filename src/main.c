/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:25:04 by rgrochow          #+#    #+#             */
/*   Updated: 2025/04/30 00:30:27 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		(printf("Usage: ./cub3D maps/<map_file>\n"), exit(0));
	check_file(argv[1]);
	init_imgs(&game, argv[1]);
	init_map(&game, argv[1]);
	check_map(&game);
	init_game(&game);
	mlx_mouse_move(game.mlx, game.win, game.win_w / 2, game.win_h / 2);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_mouse_hide(game.mlx, game.win);
	mlx_loop_hook(game.mlx, loop_hook, &game);
	mlx_loop(game.mlx);
	clear_game(&game);
	return (0);
}
