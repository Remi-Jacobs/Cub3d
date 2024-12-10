/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:59:39 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/10 03:03:35 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

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

// // our own clear_image
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

// // utils functions
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
			if (map[y][x] == '1' || map[y][x] == ' ')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, game);
			x++;
		}
		y++;
	}
}

// // touch function 
bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

int	ft_image_error(t_texture *texture)
{
	if (!texture->east_img || !texture->west_img
		|| !texture->north_img || !texture->south_img)
	{
		ft_error("east error\n");
		return (0);
	}
	return (1);
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
	if (!game->mlx)
	{
		ft_error("Error initializing MiniLibX");
		// func to sweep clean
		// ft_close_exit
		exit(EXIT_FAILURE);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, \
	&game->bpp, &game->size_line, &game->endian);
	if (!load_textures(game))
	{
		// ft_close_exit
		return ;
	}	
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
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
		perp_wall_dist = (map->x - player->player_x / BLOCK + \
		(1 - game->step_x) / 2) / game->ray_dir_x;
	else
		perp_wall_dist = (map->y - player->player_y / BLOCK + \
		(1 - game->step_y) / 2) / game->ray_dir_y;
	return (perp_wall_dist);
}
 
int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = &game->player;
	move_player(player, game);
	clear_image(game);
	if (DEBUG)
	{
		game->color = 0x00FFFF;
		draw_square(player->player_x, player->player_y, 10, game);
		draw_map(game);
	}
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		game->screen_x = i;
		draw_line(player, game, start_x);
		start_x += fraction;
		i++;
	}
	return (mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0), 0);
}

