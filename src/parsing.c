/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/12/11 11:21:42 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

// int	readfile_and_save_content(char *read_file, t_parser *element)
// {
// 	int		fd;
// 	char	*line_read;
// 	char	*trim_file;
// 	int		x;

// 	x = 0;
// 	fd = ft_open_file(read_file);
// 	if (fd == 0)
// 		return (0);
// 	while ((line_read = get_next_line(fd)) != NULL)
// 	{
// 		trim_file = ft_skip_check_element_char(line_read);
// 		if (trim_file == NULL)
// 			break ;
// 		if (trim_file[0] == '\n')
// 			continue ;
// 		if (validating_texture(trim_file, element))
// 		{
// 			if (!checking_texture(trim_file, element))
// 			{
// 				free(trim_file);
// 				return (0);
// 			}
// 			x = 1;
// 		}
// 		else if (trim_file[0] == 'C' || trim_file[0] == 'F')
// 		{
// 			if (!validating_ceiling_floor(trim_file, element))
// 			{
// 				free(trim_file);
// 				return (0);
// 			}
// 			x = 1;
// 		}
// 		else if (trim_file[0] == '1')
// 		{
// 			if (!validating_map(trim_file, element))
// 			{
// 				ft_error("\n\nhere hherehhere Invalid elemenT recieved\n");
// 				free(trim_file);
// 				return (0);
// 			}
// 			x = 1;
// 		}
// 	}
// 	free(line_read);
// 	if (x)
// 		return (1);
// 	ft_error("Invalid elemenT recieved\n");
// 	return (0);
// }

int	process_line(char *trim_file, t_parser *element, int *has_started)
{
	if (*has_started)
	{
		if (trim_file[0] == '1' || trim_file[0] == '0')
		{
			if (!validating_map(trim_file, element))
				return (0);
		}
		else
		{
			ft_error("Map out of order\n");
			return (0);
		}
	}
	else
	{
		if (validating_texture(trim_file, element))
		{
			if (!checking_texture(trim_file, element))
				return (0);
		}
		else if (trim_file[0] == 'C' || trim_file[0] == 'F')
		{
			if (!validating_ceiling_floor(trim_file, element))
				return (0);
		}
		else if (trim_file[0] == '1' || trim_file[0] == '0')
		{
			*has_started = 1;
			if (!validating_map(trim_file, element))
				return (0);
		}
	}
	return (1);
}

int	read_and_process_lines(int fd, t_parser *element)
{
	char	*line_read;
	char	*trim_file;
	int		has_started;
	int		x;

	x = 0;
	has_started = 0;
	line_read = get_next_line(fd);
	while (line_read != NULL)
	{
		trim_file = ft_skip_check_element_char(line_read);
		if (trim_file == NULL)
		{
			// free(line_read);
			x = 0;
			break;
		}
		if (trim_file[0] == '\n')
		{
			free(line_read);
			line_read = get_next_line(fd);
			continue ;
		}
		if (!process_line(trim_file, element, &has_started)){
			free(line_read);
			return (0);
		}
		x = 1;
		free(line_read);
		line_read = get_next_line(fd);
	}
	// free(line_read);
	return (x);
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
	if (access(tex->east_path, F_OK) == -1
		|| access(tex->west_path, F_OK) == -1 
		|| access(tex->south_path, F_OK) == -1
		|| access(tex->north_path, F_OK) == -1)
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
		|| !verify_colors(element->ceiling_color) || !verify_texture(element->texture))
	{
		printf("errror here\n\n\n");
		free_parser_struct(element);
		return (NULL);
	}
	if (element->map_array)
	printf("3 ...successffully got here and returing\n\n");
	return (element);
}
