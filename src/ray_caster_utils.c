/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:27:17 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/13 16:56:47 by danevans         ###   ########.fr       */
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

void	clear_image(t_game *game)
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

void	init_all(t_game *game)
{
	game->ray_dir_x = 0;
	game->ray_dir_y = 0;
	game->delta_dist_x = 0;
	game->delta_dist_y = 0 ;
	game->side_dist_x = 0;
	game->side_dist_y = 0;
	game->step_x = 0 ;
	game->step_y = 0;
	game->side = 0;
	game->line_height = 0;
	game->draw_start = 0;
	game->draw_end = 0;
	game->tex_x = 0;
	game->tex_y = 0;
	game->screen_x = 0;
	game->perp_wall_dist = 0;
	game->is_ceiling = 0; 
}

int	are_dimensions_equal(int h1, int h2, int h3, int h4)
{
	return (h1 == h2 && h1 == h3 && h1 == h4);
}

int	ft_image_error(t_texture *texture)
{
	if (!texture->east->img || !texture->west->img
		|| !texture->north->img || !texture->south->img)
	{
		ft_error("Error mlx_image failed\n");
		return (0);
	}
	if (!are_dimensions_equal(texture->east->height, texture->south->height,
			texture->west->height, texture->north->height))
	{
		ft_error("Texture map height dimension\n");
		return (0);
	}
	if (!are_dimensions_equal(texture->east->width, texture->south->width,
			texture->west->width, texture->north->width))
	{
		ft_error("Texture width diff dimension\n");
		return (0);
	}
	texture->width = texture->east->width;
	texture->height = texture->east->height; 
	return (1);
}