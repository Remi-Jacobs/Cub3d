/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:13:58 by danevans          #+#    #+#             */
/*   Updated: 2024/12/13 22:40:23 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	init_ceil_floor_color(t_parser *element)
{
	element->ceiling_color = malloc(sizeof(t_color));
	element->floor_color = malloc(sizeof(t_color));
	if (!element->ceiling_color || !element->floor_color)
	{
		ft_error("malloc failed to allocate \n");
		return (0);
	}
	element->ceiling_color->blue = -1;
	element->ceiling_color->red = -1;
	element->ceiling_color->green = -1;
	element->floor_color->blue = -1;
	element->floor_color->red = -1;
	element->floor_color->green = -1;
	element->map_index = 0;
	return (1);
}

static t_img_info	*init_texture_data(void)
{
	t_img_info	*image;

	image = malloc(sizeof(t_img_info));
	if (!image)
	{
		ft_error("MALLOC failed to allocate t_info_img failed\n");
		return (NULL);
	}
	image->bpp = 0;
	image->width = 0;
	image->endian = 0;
	image->height = 0;
	image->size_line = 0;
	image->img = NULL;
	image->data = NULL;
	image->path = NULL;
	return (image);
}

void	init_texture_maps(t_parser *element)
{
	int		i;

	i = 0;
	element->map_array = malloc(sizeof(t_map));
	if (!element->map_array)
		return (ft_error("MALLOC failed to allocate map_array\n"));
	element->map_array->map = malloc(sizeof(char *) * MAP_HEIGHT);
	if (!element->map_array->map)
		return (ft_error("MALLOC failed to allocate map_array\n"),
			free(element->map_array));
	while (i < MAP_HEIGHT)
	{
		element->map_array->map[i] = NULL;
		i++;
	}
	element->map_array->max_map_column = 0;
	element->map_array->max_map_row = 0;
	element->texture->east = init_texture_data();
	element->texture->west = init_texture_data();
	element->texture->north = init_texture_data();
	element->texture->south = init_texture_data();
	if (!element->texture->east || !element->texture->west
		|| !element->texture->north || !element->texture->south)
		ft_error("MALLOC failed to allocate textures\n");
}

t_parser	*init_elements(void)
{
	t_parser	*element;

	element = malloc(sizeof(t_parser));
	if (!element)
	{
		ft_error("malloc failed to allocate \n");
		return (NULL);
	}
	element->texture = malloc(sizeof(t_texture));
	if (!element->texture)
	{
		ft_error("malloc failed to allocate \n");
		free(element);
		return (NULL);
	}
	if (!init_ceil_floor_color(element))
	{
		free(element->texture);
		free(element);
		return (NULL);
	}
	init_texture_maps(element);
	return (element);
}

void	free_map_stored(t_parser *element)
{
	int	i;

	i = 0;
	if (element->map_array)
	{
		while (element->map_array->map[i])
		{
			if (element->map_array->map[i])
			{
				free (element->map_array->map[i]);
				element->map_array->map[i] = NULL;
			}
			i++;
		}
		free(element->map_array->map);
		element->map_array->map = NULL;
	}
	free(element->map_array);
}
