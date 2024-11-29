/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 00:00:10 by danevans          #+#    #+#             */
/*   Updated: 2024/11/27 19:30:08 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parsing/parsing.h"

//should be ensuring the len also when checking the strncmp

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
	ft_error("\n\n\n\n SHOULD Invalid Texture\n\n\n\n\n");
	return (0);
}

int	saving_texture(char *readfile, char **texture)
{
	char	*new_trim;

	readfile += 2;
	readfile = ft_iswhitespace(readfile);
	new_trim = ft_trim_newline(readfile);
	// if (!ft_open_file(new_trim))
	// 	return (0);
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
		else
		{
			ft_error("color complete\n");
			return (0);
		}
		return (1);
	}
	ft_error("color out of range\nvalid range between 0 && 255\n");
	return (0);
}

int	color_check_pass(t_color *color, char *readfile)
{
	if (color->green == -1 || color->blue == -1 || color->red == -1)
	{
		ft_error("Invalid color format\n");
		// free(readfile);
		return (0);
	}
	return (1);
}

int	saving_ceiling_and_floor(char *readfile, t_color *color)
{
	int		num;
	int		flag;
	char	*num_str;
	
	// char	*save_ptr;
	flag = 0;
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
		{
			flag = 1;
			break ;
		}
		readfile = ft_iswhitespace(readfile);
	}
	if (!color_check_pass(color, readfile) || flag)
	{
	// free(save_ptr);
		return (0);
	}
	// free(save_ptr);
	return (1);
}
