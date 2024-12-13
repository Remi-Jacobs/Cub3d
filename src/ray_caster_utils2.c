/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 20:49:23 by danevans          #+#    #+#             */
/*   Updated: 2024/12/13 22:29:31 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	assign_game_tex(t_game *game)
{
	if (game->tex_y < 0)
		game->tex_y = 0;
	if (game->tex_y >= game->element->texture->height)
		game->tex_y = game->element->texture->height -1;
}

void	free_image_data(t_img_info *texture)
{
	if (texture)
	{
		if (texture->path)
		{
			free(texture->path);
			texture->path = NULL;
		}
		free(texture);
    }
}

void	free_img_struct(t_texture *tex)
{
	if (!tex)
	{
		ft_error("empty and no data\n");
		return ;
	}
	if (tex->east)
	{
		free_image_data(tex->east);
		tex->east = NULL;
	}
	if (tex->west)
	{
		free_image_data(tex->west);
		tex->west = NULL;
	}
	if (tex->south)
	{
		free_image_data(tex->south);
		tex->south = NULL;
	}
	if (tex->north)
	{
		free_image_data(tex->north);
		tex->north = NULL;
	}
	free(tex);
	tex = NULL;
	
}
