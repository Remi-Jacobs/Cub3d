/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:27:06 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/12 12:15:58 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	get_texture_pixel(t_texture *texture, int x, int y, void *texture_data)
{
	int				offset;
	unsigned char	*data;
	int				color;

	offset = (y * texture->size_line + x * (texture->bpp / 8));
	data = (unsigned char *)texture_data;
	color = (*(int *)(data + offset));
	return (color);
}

void	init_ray(t_player *player, t_game *game, float ray_angle)
{
	game->ray_dir_x = cos(ray_angle);
	game->ray_dir_y = sin(ray_angle);
	game->delta_dist_x = fabs(1 / game->ray_dir_x);
	game->delta_dist_y = fabs(1 / game->ray_dir_y);
}

void	calculate_step_and_sidedist(t_player *player, t_game *game, t_map *map)
{
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = (player->player_x / BLOCK - map->x) \
		* game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = (map->x + 1.0 - player->player_x / BLOCK) \
		* game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (player->player_y / BLOCK - map->y) \
		* game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = (map->y + 1.0 - player->player_y / BLOCK) \
		* game->delta_dist_y;
	}
}

int	perform_dda(t_game *game, t_map *map)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x += game->delta_dist_x;
			map->x += game->step_x;
			game->side = 0;
		}
		else
		{
			game->side_dist_y += game->delta_dist_y;
			map->y += game->step_y;
			game->side = 1;
		}
		if (game->map[map->y][map->x] == '1' || game->map[map->y][map->x] == ' ')
			hit = 1;
	}
	return (game->side);
}

float	calculate_wall_distance(t_player *player, t_game *game, \
t_map *map, int side)
{
	float	perp_wall_dist;

	if (side == 0)
		perp_wall_dist = (map->x - (player->player_x / BLOCK) + \
		(1 - game->step_x) / 2) / game->ray_dir_x;
	else
		perp_wall_dist = (map->y - (player->player_y / BLOCK) + \
		(1 - game->step_y) / 2) / game->ray_dir_y;
	return (perp_wall_dist);
}

// void init_rays(t_game *game, float ray_angle)
// {
//     game->ray_dir_x = cos(ray_angle);
//     game->ray_dir_y = sin(ray_angle);
//     game->delta_dist_x = fabs(1 / game->ray_dir_x);
//     game->delta_dist_y = fabs(1 / game->ray_dir_y);
// }



// void calculate_step_and_side_dists(t_game *game, t_player *player, int *map_x, int *map_y)
// {
//     *map_x = (int)(player->player_x / BLOCK);
//     *map_y = (int)(player->player_y / BLOCK);

//     if (game->ray_dir_x < 0)
//     {
//         game->step_x = -1;
//         game->side_dist_x = (player->player_x / BLOCK - *map_x) * game->delta_dist_x;
//     }
//     else
//     {
//         game->step_x = 1;
//         game->side_dist_x = (*map_x + 1.0 - player->player_x / BLOCK) * game->delta_dist_x;
//     }

//     if (game->ray_dir_y < 0)
//     {
//         game->step_y = -1;
//         game->side_dist_y = (player->player_y / BLOCK - *map_y) * game->delta_dist_y;
//     }
//     else
//     {
//         game->step_y = 1;
//         game->side_dist_y = (*map_y + 1.0 - player->player_y / BLOCK) * game->delta_dist_y;
//     }
// }



// int perform_ddas(t_game *game, int *map_x, int *map_y)
// {
//     int hit = 0;
//     int side = 0;

//     while (!hit)
//     {
//         if (game->side_dist_x < game->side_dist_y)
//         {
//             game->side_dist_x += game->delta_dist_x;
//             *map_x += game->step_x;
//             side = 0; // Vertical wall
//         }
//         else
//         {
//             game->side_dist_y += game->delta_dist_y;
//             *map_y += game->step_y;
//             side = 1; // Horizontal wall
//         }

//         if (game->map[*map_y][*map_x] == '1')
//             hit = 1;
//     }
//     return side;
// }


// float calculate_wall_distances(t_game *game, t_player *player, int map_x, int map_y, int side)
// {
//     if (side == 0)
//         return (map_x - player->player_x / BLOCK + (1 - game->step_x) / 2) / game->ray_dir_x;
//     else
//         return (map_y - player->player_y / BLOCK + (1 - game->step_y) / 2) / game->ray_dir_y;
// }



// void draw_wall_slices(t_game *game, int screen_x, int draw_start, int draw_end, int tex_x, int side)
// {
//     for (int y = draw_start; y < draw_end; y++)
//     {
//         int tex_y = (int)(((y - draw_start) * game->element->texture->height) / game->line_height);
//         tex_y = tex_y < 0 ? 0 : tex_y;
//         tex_y = tex_y >= game->element->texture->height ? game->element->texture->height - 1 : tex_y;

//         if (side == 0 && game->ray_dir_x > 0)
//             game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->east_data);
//         else if (side == 0 && game->ray_dir_x < 0)
//             game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->west_data);
//         else if (side == 1 && game->ray_dir_y > 0)
//             game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->south_data);
//         else
//             game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->north_data);

//         put_pixel(screen_x, y, game);
//     }
// }


// void draw_ceiling_and_floors(t_game *game, int screen_x, int draw_start, int draw_end)
// {
//     for (int y = 0; y < draw_start; y++)
//     {
//         game->color = game->element->ceiling_color->converted_color;
//         put_pixel(screen_x, y, game);
//     }
//     for (int y = draw_end; y < HEIGHT; y++)
//     {
//         game->color = game->element->floor_color->converted_color;
//         put_pixel(screen_x, y, game);
//     }
// }



// void draw_lines(t_game *game, t_player *player, float ray_angle, int screen_x)
// {
//     int map_x, map_y;

//     init_rays(game, ray_angle);
//     calculate_step_and_side_dists(game, player, &map_x, &map_y);

//     int side = perform_ddas(game, &map_x, &map_y);
//     game->perp_wall_dist = calculate_wall_distances(game, player, map_x, map_y, side);

//     game->line_height = (int)(HEIGHT / game->perp_wall_dist);
//     int draw_start = -game->line_height / 2 + HEIGHT / 2;
//     if (draw_start < 0) draw_start = 0;
//     int draw_end = game->line_height / 2 + HEIGHT / 2;
//     if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

//     float wall_x = (side == 0) ? player->player_y / BLOCK + game->perp_wall_dist * game->ray_dir_y
//                                : player->player_x / BLOCK + game->perp_wall_dist * game->ray_dir_x;
//     wall_x -= floor(wall_x);

//     int tex_x = (int)(wall_x * game->element->texture->width);
//     if (side == 0 && game->ray_dir_x > 0) tex_x = game->element->texture->width - tex_x - 1;
//     if (side == 1 && game->ray_dir_y < 0) tex_x = game->element->texture->width - tex_x - 1;

//     draw_ceiling_and_floors(game, screen_x, draw_start, draw_end);
//     draw_wall_slices(game, screen_x, draw_start, draw_end, tex_x, side);
// }



// int draw_looper(t_game *game)
// {
//     t_player *player = &game->player;
//     move_player(player, game);
//     clear_image(game);

//     float fraction = PI / 3 / WIDTH;
//     float start_angle = player->angle - PI / 6;

//     for (int i = 0; i < WIDTH; i++)
//     {
//         draw_lines(game, player, start_angle, i);
//         start_angle += fraction;
//     }

//     mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
//     return 0;
// }

