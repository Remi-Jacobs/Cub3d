/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:27:06 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/13 20:46:38 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	gtex_pixel(t_img_info *texture, int x, int y, void *texture_data)
{
	int				offset;
	unsigned char	*data;
	int				color;

	offset = (y * texture->size_line + x * (texture->bpp / 8));
	data = (unsigned char *)texture_data;
	color = (*(int *)(data + offset));
	return (color);
}

int	load_textures(t_game *game)
{
	t_texture	*tex;

	tex = game->element->texture;
	tex->east->img = mlx_xpm_file_to_image(game->mlx, tex->east->path,
			&tex->east->width, &tex->east->height);
	tex->west->img = mlx_xpm_file_to_image(game->mlx, tex->west->path,
			&tex->west->width, &tex->west->height);
	tex->north->img = mlx_xpm_file_to_image(game->mlx, tex->north->path,
			&tex->north->width, &tex->north->height);
	tex->south->img = mlx_xpm_file_to_image(game->mlx, tex->south->path,
			&tex->south->width, &tex->south->height);
	if (!ft_image_error(game->element->texture))
		return (0);
	tex->north->data = mlx_get_data_addr(tex->north->img, &tex->north->bpp,
			&tex->north->size_line, &tex->north->endian);
	tex->west->data = mlx_get_data_addr(tex->west->img, &tex->west->bpp,
			&tex->west->size_line, &tex->west->endian);
	tex->east->data = mlx_get_data_addr(tex->east->img, &tex->east->bpp,
			&tex->east->size_line, &tex->east->endian);
	tex->south->data = mlx_get_data_addr(tex->south->img, &tex->south->bpp,
			&tex->south->size_line, &tex->south->endian);
	return (1);
}

void	cal_step_and_sidedist(t_player *player, t_game *game)
{
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = (player->player_x / BLOCK - player->map_x)
			* game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = (player->map_x + 1.0 - player->player_x / BLOCK)
			* game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (player->player_y / BLOCK - player->map_y)
			* game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = (player->map_y + 1.0 - player->player_y / BLOCK)
			* game->delta_dist_y;
	}
}

void	performing_dda(t_player *player, t_game *game, int *side)
{
	int	row;
	int	column;

	game->hit = 0;
	row = game->element->map_array->max_map_row;
	column = game->element->map_array->max_map_column;
	while (!game->hit)
	{
		if (player->map_x < 0 || player->map_x >= row
			|| player->map_y < 0 || player->map_y >= column)
			return ;
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x += game->delta_dist_x;
			player->map_x += game->step_x;
			*side = 0;
		}
		else
		{
			game->side_dist_y += game->delta_dist_y;
			player->map_y += game->step_y;
			*side = 1;
		}
		game->hit = check_hit(player, game);
	}
}

float	cal_wall_dist(t_player *player, t_game *game, float ray_angle, int side)
{
	float	wall_x;

	if (side == 0)
		game->perp_wall_dist = (player->map_x - player->player_x / BLOCK
				+ (1 - game->step_x) / 2) / game->ray_dir_x;
	else
		game->perp_wall_dist = (player->map_y - player->player_y / BLOCK
				+ (1 - game->step_y) / 2) / game->ray_dir_y;
	game->perp_wall_dist *= cos(ray_angle - player->angle);
	game->line_height = (int)(HEIGHT / game->perp_wall_dist);
	game->draw_start = -game->line_height / 2 + HEIGHT / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + HEIGHT / 2;
	if (game->draw_end >= HEIGHT)
		game->draw_end = HEIGHT - 1;
	if (side == 0)
		wall_x = player->player_y / BLOCK + game->perp_wall_dist
			* game->ray_dir_y;
	else
		wall_x = player->player_x / BLOCK + game->perp_wall_dist
			* game->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}
