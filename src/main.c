/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 01:44:02 by danevans          #+#    #+#             */
/*   Updated: 2024/12/13 17:00:21 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	ft_error_exit(t_parser *data, char *str)
{
	free_parser_struct(data);
	printf("%s\n", str);
}

void	init_game_utils(t_game *game)
{
	game->tex_pixels = NULL;
	game->map = game->element->map_array->map;
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
}

int	init_game(t_game *game, char *argv)
{
	game->element = parsing_func(argv);
	if (game->element == NULL)
	{
		ft_error("Error from parsing\n");
		return (0);
	}
	printf ("End of parsing\n");
	if (!init_player(&game->player, game->element->map_array))
	{
		ft_error("Error from init_player\n");
		return (0);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_error("Error initializing mlx");
		return(0);
	}
	init_game_utils(game);
	if (!load_textures(game))
	{
		ft_error("Error loading texture\n");
		return(0) ;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}

int	main(int ac, char **argv)
{
	t_game	game;

	if (!valid_extension_file_check(argv[1], ac, "cub"))
		return (0);
	init_game(&game, argv[1]);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_loop_hook(game.mlx, draw_loops, &game);
	mlx_hook(game.win, 17, 0, close_game_on_cross, &game);
	mlx_loop(game.mlx);
	free_game_struct(&game);
	return (0);
}
