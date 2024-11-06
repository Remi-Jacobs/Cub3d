/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:45:41 by danevans          #+#    #+#             */
/*   Updated: 2024/11/06 02:29:29 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_open_file(char *read_file)
{
	int	fd;

	fd = open(read_file, O_RDONLY);
	if (fd == -1)
	{
		ft_error("OPEN failed\n");
		return (0);
	}
	return (fd);
}

void	ft_free_trimmed_line_read(char *trim_line, char *line_read)
{
	if (line_read)
		free (line_read);
	if (trim_line)
		free (trim_line);
}

int	validating_texture(char *trim_file, t_parser *element)
{
	if ((ft_strncmp(trim_file, "WE", 2) == 0)
		|| (ft_strncmp(trim_file, "EA", 2) == 0)
		|| (ft_strncmp(trim_file, "NO", 2) == 0)
		|| (ft_strncmp(trim_file, "SO", 2) == 0))
	{
		return (1);
	}
	return (0);
}

int	validating_ceiling_floor(char *trim_file, t_parser *element)
{
	if (ft_strncmp(trim_file, "C", 1) == 0)
	{
		saving_ceiling_and_floor(trim_file, element->ceiling_color);
		return (1);
	}
	else if (ft_strncmp(trim_file, "F", 1) == 0)
	{
		saving_ceiling_and_floor(trim_file, element->floor_color);
		return (1);
	}
	return (0);
}

int	readfile_and_save_content(char *read_file, t_parser *element)
{
	int		fd;
	char	*line_read;
	char	*trim_file;

	fd = ft_open_file(read_file);
	if (fd == 0)
		return (0);
	line_read = get_next_line(fd);
	while (line_read != NULL)
	{
		trim_file = ft_skip_whitespace(line_read);
		if (trim_file[0] == '\n')
			continue ;
		if (trim_file == NULL)
			break ;
		if (validating_texture(trim_file, element))
		{
			if (!checking_texture(trim_file, element))
				break ;
		}
		else if (trim_file[0] == 'C' || trim_file[0] == 'F')
		{
			if (!validating_ceiling_floor(trim_file, element))
				break ;
		}
		else if (!validating_map(trim_file, element))
			break ;
		ft_free_trimmed_line_read(trim_file, line_read);
		line_read = get_next_line(fd);
	}
	ft_error("Invalid element recieved\n");
	ft_free_trimmed_line_read(trim_file, line_read);
	return (0);
}
