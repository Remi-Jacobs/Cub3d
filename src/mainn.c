/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:59:39 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/12 20:34:46 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	put_pixel(int x, int y, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
    	return;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = game->color & 0xFF;
	game->data[index + 1] = (game->color >> 8) & 0xFF;
	game->data[index + 2] = (game->color >> 16) & 0xFF;
}

void clear_image(t_game *game)
{
	int	i;
    int	*img_data;
	int	total_pixels;

	i = 0;
	img_data = (int *)game->data;
    total_pixels = WIDTH * HEIGHT;
	while (i < total_pixels)
	{
		img_data[i] = 0x000000;
		i++;
	}
}

int	ft_image_error(t_texture *texture)
{
	if (!texture->east_img || !texture->west_img
		|| !texture->north_img || !texture->south_img)
	{
		ft_error("Error mlx_image failed\n");
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	t_texture *tex;

	tex = game->element->texture;
	tex->east_img = mlx_xpm_file_to_image(game->mlx, tex->east_path,
		&tex->width, &tex->height);
	tex->west_img = mlx_xpm_file_to_image(game->mlx, tex->west_path,
		&tex->width, &tex->height);
	tex->north_img = mlx_xpm_file_to_image(game->mlx, tex->north_path,
		&tex->width, &tex->height);
	tex->south_img = mlx_xpm_file_to_image(game->mlx, tex->south_path,
		&tex->width, &tex->height);
	if (!ft_image_error(game->element->texture))
		return (0);
	tex->north_data = mlx_get_data_addr(tex->north_img, &tex->bpp,
		&tex->size_line, &tex->endian);
	tex->west_data = mlx_get_data_addr(tex->west_img, &tex->bpp,
		&tex->size_line, &tex->endian);
	tex->east_data = mlx_get_data_addr(tex->east_img, &tex->bpp,
		&tex->size_line, &tex->endian);
	tex->south_data = mlx_get_data_addr(tex->south_img, &tex->bpp,
		&tex->size_line, &tex->endian);
	return(1);
}

//2d map
void	draw_square(int x, int y, int size, t_game *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, game);
	i = -1;
	while (++i < size)
		put_pixel(x, y + i, game);
	i = -1;
	while (++i < size)
		put_pixel(x + size, y + i, game);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size, game);
}
//2d map
void	draw_map(t_game *game)
{
	char	**map;
	int		y;
	int		x;

	map = game->map;
	y = 0;
	game->color = 0xFF0000;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, game);
			x++;
		}
		y++;
	}
}


 void draw_lines(t_player *player, t_game *game, float ray_angle, int screen_x)
{
	// Ray initialization
	game->ray_dir_x = cos(ray_angle);
	game->ray_dir_y = sin(ray_angle);

	int map_x = (int)(player->player_x / BLOCK);
	int map_y = (int)(player->player_y / BLOCK);

	game->delta_dist_x = fabs(1 / game->ray_dir_x);
	game->delta_dist_y = fabs(1 / game->ray_dir_y);

	// Calculate step and initial side_dist
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = (player->player_x / BLOCK - map_x) * game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = (map_x + 1.0 - player->player_x / BLOCK) * game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (player->player_y / BLOCK - map_y) * game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = (map_y + 1.0 - player->player_y / BLOCK) * game->delta_dist_y;
	}

	// Perform DDA
	int hit = 0;
	int side; // 0: vertical wall, 1: horizontal wall
	while (!hit)
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x += game->delta_dist_x;
			map_x += game->step_x;
			side = 0; // Vertical wall
		}
		else
		{
			game->side_dist_y += game->delta_dist_y;
			map_y += game->step_y;
			side = 1; // Horizontal wall
		}

		// Check for wall hit
		if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
			hit = 1;
	}

	// Calculate perpendicular distance to the wall
	float perp_wall_dist;
	if (side == 0)
		perp_wall_dist = (map_x - player->player_x / BLOCK + (1 - game->step_x) / 2) / game->ray_dir_x;
	else
		perp_wall_dist = (map_y - player->player_y / BLOCK + (1 - game->step_y) / 2) / game->ray_dir_y;


	// Correct for fish-eye effect
	perp_wall_dist *= cos(ray_angle - player->angle);

	// Calculate line height and rendering range
	int line_height = (int)(HEIGHT / perp_wall_dist);
	int draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;

	// Calculate wall hit position for texture mapping
	float wall_x;
	if (side == 0)
		wall_x = player->player_y / BLOCK + perp_wall_dist * game->ray_dir_y;
	else
		wall_x = player->player_x / BLOCK + perp_wall_dist * game->ray_dir_x;
	wall_x -= floor(wall_x);

	int tex_x = (int)(wall_x * game->element->texture->width);
	if (side == 0 && game->ray_dir_x > 0)
		tex_x = game->element->texture->width - tex_x - 1;
	if (side == 1 && game->ray_dir_y < 0)
		tex_x = game->element->texture->width - tex_x - 1;

	// Draw the wall slice
	for (int y = draw_start; y < draw_end; y++)
	{
		int tex_y = (int)(((y - HEIGHT / 2 + line_height / 2) * game->element->texture->height) / line_height);
		tex_y = tex_y < 0 ? 0 : tex_y;
		tex_y = tex_y >= game->element->texture->height ? game->element->texture->height - 1 : tex_y;

		// Fetch the texture color based on the side of the wall and ray direction
		if (side == 0 && game->ray_dir_x> 0)
			game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->east_data);
		else if (side == 0 && game->ray_dir_x < 0)
			game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->west_data);
		else if (side == 1 && game->ray_dir_y > 0)
			game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->south_data);
		else
			game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->north_data);

		put_pixel(screen_x, y, game);
	}

	// Draw ceiling
	int y = 0;
	while (y < draw_start)
	{
		game->color = game->element->ceiling_color->converted_color;
		put_pixel(screen_x, y, game);
		y++;
	}

	// Draw floor
	y = draw_end;
	while (y < HEIGHT)
	{
		game->color = game->element->floor_color->converted_color;
		put_pixel(screen_x, y, game);
		y++;
	}
}

// int	draw_loop(t_game *game)
// {
// 	t_player	*player;
// 	float		fraction;
// 	float		start_x;
// 	int			i;

// 	player = &game->player;
// 	move_player(player, game);
// 	clear_image(game);
// 	//removing this after
// 	// if (DEBUG)
// 	// {
// 	// 	game->color = 0x00FFFF;
// 	// 	draw_square(player->player_x, player->player_y, BLOCK / 4 , game);
// 	// 	draw_map(game);
// 	// }
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

int draw_loops(t_game *game)
{
	t_player *player = &game->player;
	move_player(player, game);
	clear_image(game);

	if (DEBUG)
	{
		game->color = 0x00FFFF;
		draw_square(player->player_x, player->player_y, 10, game);
		draw_map(game);
	}

	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	int i = 0;

	while (i < WIDTH)
	{

		draw_lines(player, game, start_x, i);
		start_x += fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}
