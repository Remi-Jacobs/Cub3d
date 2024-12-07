/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:32:05 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/07 04:03:37 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

// void	load_textures(t_game *game)
// {
// 	game->element->texture->east_img = mlx_xpm_file_to_image(game->mlx, \
// 	"./Tower_Blue.xpm", &game->element->texture->width, \
// 	&game->element->texture->height);
// 	game->element->texture->east_data = mlx_get_data_addr \
// 	(game->element->texture->east_img, &game->element->texture->bpp, \
// 	&game->element->texture->size_line, &game->element->texture->endian);
// 	game->element->texture->west_img = mlx_xpm_file_to_image(game->mlx, \
// 	"./Tower_Red.xpm", &game->element->texture->width, \
// 	&game->element->texture->height);
// 	game->element->texture->west_data = mlx_get_data_addr \
// 	(game->element->texture->west_img, &game->element->texture->bpp, \
// 	&game->element->texture->size_line, &game->element->texture->endian);
// 	game->element->texture->north_img = mlx_xpm_file_to_image(game->mlx, \
// 	"./Gate_Closed.xpm", &game->element->texture->width, \
// 	&game->element->texture->height);
// 	game->element->texture->north_data = mlx_get_data_addr \
// 	(game->element->texture->north_img, &game->element->texture->bpp, \
// 	&game->element->texture->size_line, &game->element->texture->endian);
// 	game->element->texture->south_img = mlx_xpm_file_to_image(game->mlx, \
// 	"./Mushroom.xpm", &game->element->texture->width, \
// 	&game->element->texture->height);
// 	game->element->texture->south_data = mlx_get_data_addr \
// 	(game->element->texture->south_img, &game->element->texture->bpp, \
// 	&game->element->texture->size_line, &game->element->texture->endian);
// }

// // initialisation functions

// void	init_game(t_game *game, char *argv)
// {
// 	game->element = parsing_func(argv);
// 	if (game->element == NULL)
// 		return ;
// 	init_player(&game->player, game->element->map_array);
// 	game->tex_pixels = NULL;
// 	game->map = game->element->map_array->map;
// 	game->mlx = mlx_init();
// 	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
// 	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
// 	game->data = mlx_get_data_addr(game->img, \
// 	&game->bpp, &game->size_line, &game->endian);
// 	load_textures(game);
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// }

// int	draw_loop(t_game *game)
// {
// 	t_player	*player;
// 	float		fraction;
// 	float		start_x;
// 	int			i;

// 	player = &game->player;
// 	move_player(player, game);
// 	clear_image(game);
// 	if (DEBUG)
// 	{
// 		game->color = 0x00FFFF;
// 		draw_square(player->player_x, player->player_y, 10, game);
// 		draw_map(game);
// 	}
// 	fraction = PI / 3 / WIDTH;
// 	start_x = player->angle - PI / 6;
// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		game->screen_x = i;
// 		draw_line(player, game, start_x);
// 		start_x += fraction;
// 		i++;
// 	}
// 	return (mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0), 0);
// }
