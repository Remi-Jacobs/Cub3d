/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/12/13 16:47:55 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	free_parser_struct(t_parser *element)
{
	if (!element)
		return ;
	free_map_stored(element);
	free(element->ceiling_color);
	free(element->floor_color);
	free(element);
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
	if (access(tex->east->path, F_OK) == -1
		|| access(tex->west->path, F_OK) == -1
		|| access(tex->south->path, F_OK) == -1
		|| access(tex->north->path, F_OK) == -1)
	{
		ft_error("can't access texture\n");
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
	printf("1 .....successffully after init \n\n\n");
	if (!readfile_and_save_content(read_file, element))
	{
		free_parser_struct(element);
		printf("\nbad here\n\n\n");
		return (NULL);
	}
	printf("2.....successffully got here\n\n\n");
	if (!verify_map_walls(element) || !verify_colors(element->floor_color)
		|| !verify_colors(element->ceiling_color)
		|| !verify_texture(element->texture))
	{
		printf("errror here\n\n\n");
		free_parser_struct(element);
		return (NULL);
	}
	return (element);
}
