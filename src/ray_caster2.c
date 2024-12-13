/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:27:17 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/13 13:11:38 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

// void	draw_wall(t_game *game)
// {
// 	int	y;

// 	y = game->draw_start - 1;
// 	while (++y < game->draw_end)
// 	{
// 		// game->tex_y = (int)(((y - HEIGHT / 2 + game->line_height / 2) * game->element->texture->height) / game->line_height);
// 		// // game->tex_y = (int)(((y - game->draw_start) * game->element->texture->height) 
//         // //            / game->line_height);
// 		game->tex_y = (int)(((y - game->draw_start) * game->element->texture->east->height) / game->line_height);
// 		if (game->tex_y < 0)
// 			game->tex_y = 0;
// 		if (game->tex_y >= game->element->texture->east->height)
// 			game->tex_y = game->element->texture->east->height - 1;
// 		if (game->side == 0 && game->ray_dir_x > 0)
// 			game->color = get_texture_pixel(game->element->texture->east, \
// 			game->tex_x, game->tex_y, game->element->texture->east->data);
// 		else if (game->side == 0 && game->ray_dir_x < 0)
// 			game->color = get_texture_pixel(game->element->texture->west, \
// 			game->tex_x, game->tex_y, game->element->texture->west->data);
// 		else if (game->side == 1 && game->ray_dir_y > 0)
// 			game->color = get_texture_pixel(game->element->texture->south, \
// 			game->tex_x, game->tex_y, game->element->texture->south->data);
// 		else
// 			game->color = get_texture_pixel(game->element->texture->north, \
// 			game->tex_x, game->tex_y, game->element->texture->north->data);
// 		put_pixel(game->screen_x, y, game);
// 	}
// }

// void	draw_ceiling_floor(t_game *game)
// {
// 	int	y;

// 	y = 0;
// 	while (y < game->draw_start)
// 	{
// 		game->color = game->element->ceiling_color->converted_color;
// 		put_pixel(game->screen_x, y, game);
// 		y++;
// 	}
// 	y = game->draw_end;
// 	while (y < HEIGHT)
// 	{
// 		game->color = game->element->floor_color->converted_color;
// 		put_pixel(game->screen_x, y, game);
// 		y++;
// 	}
// }

// void	draw_ceiling_floor_wall(t_game *game)
// {
// 	game->is_ceiling = 1;
// 	draw_ceiling_floor(game);
// 	game->is_ceiling = 0;
// 	draw_ceiling_floor(game);
// 	draw_wall(game);
// }

// void	start_draw_line(t_game *game)
// {
// 	game->line_height = (int)(HEIGHT / game->perp_wall_dist);
// 	game->draw_start = -game->line_height / 2 + HEIGHT / 2;
// 	if (game->draw_start < 0)
// 		game->draw_start = 0;
// 	game->draw_end = game->line_height / 2 + HEIGHT / 2;
// 	if (game->draw_end >= HEIGHT)
// 		game->draw_end = HEIGHT - 1;
// }

// void	draw_line(t_player *player, t_game *game, float ray_angle)
// {
// 	t_map	map;
// 	float	wall_x;

// 	init_ray(player, game, ray_angle);
// 	map.x = (int)(player->player_x / BLOCK);
// 	map.y = (int)(player->player_y / BLOCK);
// 	calculate_step_and_sidedist(player, game, &map);
// 	game->side = perform_dda(game, &map);
// 	game->perp_wall_dist = calculate_wall_distance(player, game, &map, game->side);
// 	start_draw_line(game);
// 	if (game->side == 0)
// 		wall_x = player->player_y / BLOCK + \
// 		game->perp_wall_dist * game->ray_dir_y;
// 	else
// 		wall_x = player->player_x / BLOCK + \
// 		game->perp_wall_dist * game->ray_dir_x;
// 	wall_x -= floor(wall_x);
// 	game->tex_x = (int)(wall_x * game->element->texture->width);
// 	if (game->side == 0 && game->ray_dir_x > 0)
// 		game->tex_x = game->element->texture->width - game->tex_x - 1;
// 	if (game->side == 1 && game->ray_dir_y < 0)
// 		game->tex_x = game->element->texture->width - game->tex_x - 1;
// 	draw_ceiling_floor_wall(game);
// }

