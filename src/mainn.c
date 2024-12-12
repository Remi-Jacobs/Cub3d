/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:59:39 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/12 12:16:25 by danevans         ###   ########.fr       */
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
			if (map[y][x] == '1' || map[y][x] == ' ')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, game);
			x++;
		}
		y++;
	}
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
	//removing this after
	// if (DEBUG)
	// {
	// 	game->color = 0x00FFFF;
	// 	draw_square(player->player_x, player->player_y, BLOCK / 4 , game);
	// 	draw_map(game);
	// }
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

