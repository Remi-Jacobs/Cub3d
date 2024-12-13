/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:59:39 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/13 20:50:23 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	init_ray_pos(t_player *player, t_game *game, float ray_angle)
{
	game->ray_dir_x = cos(ray_angle);
	game->ray_dir_y = sin(ray_angle);
	player->map_x = (int)(player->player_x / BLOCK);
	player->map_y = (int)(player->player_y / BLOCK);
	game->delta_dist_x = fabs(1 / game->ray_dir_x);
	game->delta_dist_y = fabs(1 / game->ray_dir_y);
}

void	drawing_ceiling_floor(t_game *game, int screen_x)
{
	int	y;

	y = 0;
	while (y < game->draw_start)
	{
		game->color = game->element->ceiling_color->converted_color;
		put_pixel(screen_x, y, game);
		y++;
	}
	y = game->draw_end;
	while (y < HEIGHT)
	{
		game->color = game->element->floor_color->converted_color;
		put_pixel(screen_x, y, game);
		y++;
	}
}

void	draw_map_walls(t_game *game, int side, int screen_x)
{
	int	y;

	y = game->draw_start;
	while (y < game->draw_end)
	{
		game->tex_y = (int)(((y - HEIGHT / 2 + game->line_height / 2)
					* game->element->texture->height) / game->line_height);
		assign_game_tex(game);
		if (side == 0 && game->ray_dir_x > 0)
			game->color = gtex_pixel(game->element->texture->east, game->tex_x,
					game->tex_y, game->element->texture->east->data);
		else if (side == 0 && game->ray_dir_x < 0)
			game->color = gtex_pixel(game->element->texture->west, game->tex_x,
					game->tex_y, game->element->texture->west->data);
		else if (side == 1 && game->ray_dir_y > 0)
			game->color = gtex_pixel(game->element->texture->south, game->tex_x,
					game->tex_y, game->element->texture->south->data);
		else
			game->color = gtex_pixel(game->element->texture->north, game->tex_x,
					game->tex_y, game->element->texture->north->data);
		put_pixel(screen_x, y, game);
		y++;
	}
}

void	draw_lines(t_player *player, t_game *game,
float ray_angle, int screen_x)
{
	int		side;
	float	wall_x;

	init_ray_pos(player, game, ray_angle);
	cal_step_and_sidedist(player, game);
	performing_dda(player, game, &side);
	wall_x = cal_wall_dist(player, game, ray_angle, side);
	game->tex_x = (int)(wall_x * game->element->texture->width);
	if (side == 0 && game->ray_dir_x > 0)
		game->tex_x = game->element->texture->width - game->tex_x - 1;
	if (side == 1 && game->ray_dir_y < 0)
		game->tex_x = game->element->texture->width - game->tex_x - 1;
	draw_map_walls(game, side, screen_x);
	drawing_ceiling_floor(game, screen_x);
}

int	draw_loops(t_game *game)
{
	int			i;
	float		start_x;
	float		fraction;
	t_player	*player;

	i = 0;
	init_all(game);
	player = &game->player;
	move_player(player, game);
	clear_image(game);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	while (i < WIDTH)
	{
		draw_lines(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
