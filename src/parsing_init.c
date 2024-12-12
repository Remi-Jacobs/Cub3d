/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:13:58 by danevans          #+#    #+#             */
/*   Updated: 2024/12/10 15:27:02 by danevans         ###   ########.fr       */
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

void	init_texture_maps(t_parser *element)
{
	int		i;

	i = 0;
	element->map_array = malloc(sizeof(t_map));
	if (!element->map_array)
	{
		ft_error("malloc failed to allocate map_array\n");
		return;
	}
	element->map_array->map = malloc(sizeof(char *) * MAP_HEIGHT);
	if (!element->map_array->map)
	{
		ft_error("malloc failed to allocate map_array\n");
		return;
	}
	while (i < MAP_HEIGHT)
	{
		element->map_array->map[i]	= NULL;
		i++;
	}
	element->map_array->map[MAP_HEIGHT] = NULL;
	element->map_array->max_map_column = 0;
	element->map_array->max_map_row = 0;
	element->texture->west_data = NULL;
	element->texture->east_data = NULL;
	element->texture->south_data = NULL;
	element->texture->north_data = NULL;
	element->texture->east_path = NULL;
	element->texture->west_path = NULL;
	element->texture->north_path = NULL;
	element->texture->south_path = NULL;
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

void	free_parser_struct(t_parser *element)
{
	if (!element)
		return ;
	free_map_stored(element);
	if (element->texture)
	{
		free(element->texture->east_path);
		free(element->texture->west_path);
		free(element->texture->north_path);
		free(element->texture->south_path);
	}
	free(element->texture);
	free(element->ceiling_color);
	free(element->floor_color);
	free(element);
}
