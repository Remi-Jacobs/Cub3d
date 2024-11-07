/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:13:58 by danevans          #+#    #+#             */
/*   Updated: 2024/11/07 20:42:39 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	init_ceil_floor_color(t_parser *element)
{
	element->ceiling_color = malloc(sizeof(t_color));
	element->floor_color = malloc(sizeof(t_color));
	element->map = malloc(sizeof(char *) * MAP_HEIGHT);
	if (!element->ceiling_color || !element->floor_color || !element->map)
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
	int	i;

	i = 0;
	while (i < MAP_HEIGHT)
	{
		element->map[i]	= NULL;
		i++;
	}
	element->texture->west = NULL;
	element->texture->east = NULL;
	element->texture->south = NULL;
	element->texture->north = NULL;
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
	if (element->map)
	{
		while (element->map[i])
		{
			if (element->map[i])
				free (element->map[i]);
			i++;
		}
		free(element->map);
	}
}

void	free_parser_struct(t_parser *element)
{
	if (!element)
		return ;
	free_map_stored(element);
	if (element->texture)
	{
		free(element->texture->east);
		free(element->texture->west);
		free(element->texture->north);
		free(element->texture->south);
		free(element->texture);
	}
	free(element->ceiling_color);
	free(element->floor_color);
	free(element);
}
