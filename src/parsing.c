/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/12/14 16:36:51 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	free_parser_struct(t_parser *element)
{
	if (!element)
		return ;
	free_map_stored(element);
	free_img_struct(element->texture);
	if (element->ceiling_color)
		free(element->ceiling_color);
	if (element->floor_color)
		free(element->floor_color);
	free(element);
	element = NULL;
}

int	readfile_and_save_content(char *read_file, t_parser *element)
{
	int		fd;
	int		x;

	fd = ft_open_file(read_file);
	if (fd == 0)
		return (0);
	x = read_and_process_lines(fd, element);
	if (x)
		return (1);
	ft_error("Invalid element received\n");
	return (0);
}

static int	verify_colors(t_color *color)
{
	if (color->green == -1 || color->blue == -1 || color->red == -1)
	{
		ft_error("Invalid color format\n");
		return (0);
	}
	return (1);
}

static int	verify_texture(t_texture *tex)
{
	if (!tex->east->path || !tex->west->path
		|| !tex->north->path || !tex->south->path)
		return (0);
	if (access(tex->east->path, F_OK) == -1
		|| access(tex->west->path, F_OK) == -1
		|| access(tex->south->path, F_OK) == -1
		|| access(tex->north->path, F_OK) == -1)
	{
		ft_error("can't access texture with access func\n");
		return (0);
	}
	return (1);
}

t_parser	*parsing_func(char *read_file)
{
	t_parser	*element;

	element = init_elements();
	if (element == NULL)
		return (NULL);
	if (!readfile_and_save_content(read_file, element))
	{
		ft_error("Error from readfile parsing func\n");
		free_parser_struct(element);
		return (NULL);
	}
	if (!verify_map_walls(element) || !verify_colors(element->floor_color)
		|| !verify_colors(element->ceiling_color)
		|| !verify_texture(element->texture))
	{
		ft_error("Error verifying_wall/color/ceiling/texture parsing func\n");
		free_parser_struct(element);
		return (NULL);
	}
	return (element);
}
