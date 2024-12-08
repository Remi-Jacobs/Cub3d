/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 01:44:02 by danevans          #+#    #+#             */
/*   Updated: 2024/12/08 04:49:58 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../mlx/mlx.h"

// #define TILE_SIZE 32
// #define WIN_WIDTH 800
// #define WIN_HEIGHT 600

// #define MINIMAP_WIDTH 200
// #define MINIMAP_HEIGHT 150

// void	ft_error_exit(t_parser *data, char *str)
// {
// 	free_parser_struct(data);
// 	printf("%s\n", str);
// }


// Function to create an image filled with a color
// void	*create_color_image(t_parser *data, int color)
// {
// 	int *pixels;
// 	void *img;
// 	int width = TILE_SIZE;
// 	int height = TILE_SIZE;
// 	int bpp, size_line, endian;

// 	img = mlx_new_image(data->mlx_ptr, width, height);
// 	if (!img)
// 		return (NULL);
// 	pixels = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
// 	if (!pixels)
// 		return (NULL);
// 	int i = -1;
// 	while (++i < width * height)
// 		pixels[i] = color;

// 	return (img);
// }

int	close_game_on_cross(t_game *game)
{
	close_game(game);
	return (0);
}

int	close_game(t_game *game)
{
	// mlx_destroy_image(game->mlx, game->img_player);
	// mlx_destroy_image(game->mlx, game->img_wall);
	// mlx_destroy_image(game->mlx, game->img_collectible);
	// mlx_destroy_image(game->mlx, game->img_exit);
	// mlx_destroy_image(game->mlx, game->img_floor);
	// mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->win = NULL;
	game->mlx = NULL;
	// free_map(game);
	exit(0);
}

int	main(int ac, char **argv)
{
	t_game	game;

	if (!valid_extension_file_check(argv[1], ac, "cub"))
		return (0);
	init_game(&game, argv[1]);
	// mlx_hook(game.win, 2, 1L << 0, key_press, &game.player);
	// mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	// mlx_loop_hook(game.mlx, draw_loop, &game);
	// mlx_hook(game.win, 17, 0, close_game_on_cross, &game);
	// mlx_loop(game.mlx);
	free_parser_struct(game.element);
	return (0);
}


