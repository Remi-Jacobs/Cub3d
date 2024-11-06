/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/11/06 04:20:51 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int	init_ceil_floor_color(t_parser *element)
{
	element->ceiling_color = malloc(sizeof(t_color));
	element->floor_color = malloc(sizeof(t_color));
	if (!element->ceiling_color || !element->floor_color)
	{
		ft_error("malloc failed to allocate \n");
		return (0);
	}
	element->ceiling_color->blue = 0;
	element->ceiling_color->red = 0;
	element->ceiling_color->green = 0;
	element->floor_color->blue = 0;
	element->floor_color->red = 0;
	element->floor_color->green = 0;
	return (1);
}

void	init_texture(t_parser *element)
{
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
	init_texture(element);
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

char	*ft_iswhitespace(char *readfile)
{
	while (*readfile)
	{
		if (*readfile == ' ' || (*readfile >= 9 && *readfile <= 13))
			readfile++;
		else
			break ;
	}
	return ((char *)readfile);
}

t_parser	*parsing_func(char *read_file)
{
	t_parser	*element;

	element = init_elements();
	if (element == NULL)
		return (NULL);
	printf("successffully got here\n\n\n");
	if (!readfile_and_save_content(read_file, element))
	{
		printf("and now here\n\n\n");
		free_parser_struct(element);
		return (NULL);
	}
	return (element);
}

int	main(int ac, char **argv)
{
	t_parser	*parser;

	if (!valid_extension_args_no(argv[1], ac, "cub"))
		return (0);
	parser = parsing_func(argv[1]);
	if (parser == NULL)
		return (0);
	return (0);
}