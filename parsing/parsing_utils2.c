/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:00:10 by danevans          #+#    #+#             */
/*   Updated: 2024/11/07 21:43:54 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/parsing.h"

int	checking_texture(char *readfile, t_parser *element)
{
	if (ft_strncmp(readfile, "WE", 2) == 0)
	{
		if (saving_texture(readfile, &element->texture->west))
			return (1);
	}
	else if (ft_strncmp(readfile, "EA", 2) == 0)
	{
		if (saving_texture(readfile, &element->texture->east))
			return (1);
	}
	else if (ft_strncmp(readfile, "NO", 2) == 0)
	{
		if (saving_texture(readfile, &element->texture->north))
			return (1);
	}
	else if (ft_strncmp(readfile, "SO", 2) == 0)
	{
		if (saving_texture(readfile, &element->texture->south))
			return (1);
	}
	ft_error("Invalid Texture");
	return (0);
}

int	saving_texture(char *readfile, char **texture)
{
	char	*new_trim;

	readfile += 2;
	readfile = ft_iswhitespace(readfile);
	new_trim = ft_trim_newline(readfile);
	if (!valid_extension_args_no(new_trim, 2, "xpm"))
	{
		free(new_trim);
		return (0);
	}
	*texture = ft_strdup(new_trim);
	printf("from parsing_utils2.c here --> %s\n", *texture);
	free(new_trim);
	return (1);
}

int	num_range(int num, t_color *color)
{
	if (num >= 0 && num <= 255)
	{
		if (color->red == -1)
			color->red = num;
		else if (color->green == -1)
			color->green = num;
		else if (color->blue == -1)
			color->blue = num;
		return (1);
	}
	ft_error("color out of range\n");
	return (0);
}

int	color_check_pass(t_color *color, char *readfile)
{
	if (color->green == -1 || color->blue == -1 || color->red == -1)
	{
		ft_error("Invalid color format\n");
		free(readfile);
		return (0);
	}
	return (1);
}

int	saving_ceiling_and_floor(char *readfile, t_color *color)
{
	int		num;
	char	*num_str;
	// char	*save_ptr;

	// save_ptr = readfile;
	while (*readfile != '\0')
	{
		num_str = readfile;
		while (*readfile != ',' && *readfile != '\0')
			readfile++;
		if (*readfile == ',')
		{
			*readfile = '\0';
			readfile++;
		}
		num = ft_atoi(num_str);
		if (!num_range(num, color))
			break ;
		readfile = ft_iswhitespace(readfile);
	}
	if (!color_check_pass(color, readfile))
	{		
	// free(save_ptr);
		return (0);
	}
	// free(save_ptr);
	return (1);
}
