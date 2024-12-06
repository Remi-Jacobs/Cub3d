/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:59:39 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/06 02:35:58 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

// our own put_pixel

void	put_pixel(int x, int y, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = game->color & 0xFF;
	game->data[index + 1] = (game->color >> 8) & 0xFF;
	game->data[index + 2] = (game->color >> 16) & 0xFF;
}

// our own clear_image
void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			game->color = 0;
			put_pixel(x, y, game);
			x++;
		}
		y++;
	}
}

// utils functions
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

// touch function 
bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1' || game->map[y][x] == ' ')
		return (true);
	return (false);
}

void	load_textures(t_game *game)
{
	game->element->texture->east_img = mlx_xpm_file_to_image(game->mlx, \
	"./Tower_Blue.xpm", &game->element->texture->width, \
	&game->element->texture->height);
	game->element->texture->east_data = mlx_get_data_addr \
	(game->element->texture->east_img, &game->element->texture->bpp, \
	&game->element->texture->size_line, &game->element->texture->endian);
	game->element->texture->west_img = mlx_xpm_file_to_image(game->mlx, \
	"./Tower_Red.xpm", &game->element->texture->width, \
	&game->element->texture->height);
	game->element->texture->west_data = mlx_get_data_addr \
	(game->element->texture->west_img, &game->element->texture->bpp, \
	&game->element->texture->size_line, &game->element->texture->endian);
	game->element->texture->north_img = mlx_xpm_file_to_image(game->mlx, \
	"./Gate_Closed.xpm", &game->element->texture->width, \
	&game->element->texture->height);
	game->element->texture->north_data = mlx_get_data_addr \
	(game->element->texture->north_img, &game->element->texture->bpp, \
	&game->element->texture->size_line, &game->element->texture->endian);
	game->element->texture->south_img = mlx_xpm_file_to_image(game->mlx, \
	"./Mushroom.xpm", &game->element->texture->width, \
	&game->element->texture->height);
	game->element->texture->south_data = mlx_get_data_addr \
	(game->element->texture->south_img, &game->element->texture->bpp, \
	&game->element->texture->size_line, &game->element->texture->endian);
}

// initialisation functions

void	init_game(t_game *game, char *argv)
{
	game->element = parsing_func(argv);
	if (game->element == NULL)
		return ;
	init_player(&game->player, game->element->map_array);
	game->tex_pixels = NULL;
	game->map = game->element->map_array->map;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, \
	&game->bpp, &game->size_line, &game->endian);
	load_textures(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	get_texture_pixel(t_texture *texture, int x, int y, char *texture_data)
{
	int				offset;
	unsigned char	*data;
	int				color;

	offset = (y * texture->size_line + x * (texture->bpp / 8));
	data = (unsigned char *)texture_data;
	color = (*(int *)(data + offset));
	return (color);
}

void draw_line(t_player *player, t_game *game, float ray_angle, int screen_x)
{
	// Ray initialization
	float ray_dir_x = cos(ray_angle);
	float ray_dir_y = sin(ray_angle);

	int map_x = (int)(player->player_x / BLOCK);
	int map_y = (int)(player->player_y / BLOCK);

	float delta_dist_x = fabs(1 / ray_dir_x);
	float delta_dist_y = fabs(1 / ray_dir_y);

	float side_dist_x, side_dist_y;
	int step_x, step_y;

	// Calculate step and initial side_dist
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (player->player_x / BLOCK - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - player->player_x / BLOCK) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (player->player_y / BLOCK - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - player->player_y / BLOCK) * delta_dist_y;
	}

	// Perform DDA
	int hit = 0;
	int side; // 0: vertical wall, 1: horizontal wall
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0; // Vertical wall
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; // Horizontal wall
		}

		// Check for wall hit
		if (game->map[map_y][map_x] == '1')
			hit = 1;
	}

	// Calculate perpendicular distance to the wall
	float perp_wall_dist;
	if (side == 0)
		perp_wall_dist = (map_x - player->player_x / BLOCK + (1 - step_x) / 2) / ray_dir_x;
	else
		perp_wall_dist = (map_y - player->player_y / BLOCK + (1 - step_y) / 2) / ray_dir_y;

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
		wall_x = player->player_y / BLOCK + perp_wall_dist * ray_dir_y;
	else
		wall_x = player->player_x / BLOCK + perp_wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);

	int tex_x = (int)(wall_x * game->element->texture->width);
	if (side == 0 && ray_dir_x > 0)
		tex_x = game->element->texture->width - tex_x - 1;
	if (side == 1 && ray_dir_y < 0)
		tex_x = game->element->texture->width - tex_x - 1;

	// Draw the wall slice
	for (int y = draw_start; y < draw_end; y++)
	{
		int tex_y = (int)(((y - HEIGHT / 2 + line_height / 2) * game->element->texture->height) / line_height);
		tex_y = tex_y < 0 ? 0 : tex_y;
		tex_y = tex_y >= game->element->texture->height ? game->element->texture->height - 1 : tex_y;

		// Fetch the texture color based on the side of the wall and ray direction
		if (side == 0 && ray_dir_x > 0)
			game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->east_data);
		else if (side == 0 && ray_dir_x < 0)
			game->color = get_texture_pixel(game->element->texture, tex_x, tex_y, game->element->texture->west_data);
		else if (side == 1 && ray_dir_y > 0)
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

int draw_loop(t_game *game)
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
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

