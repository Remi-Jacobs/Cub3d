/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:45:41 by danevans          #+#    #+#             */
/*   Updated: 2024/11/01 20:42:12 by danevans         ###   ########.fr       */
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

int	validating_texture(char *trim_file)
{
	if ((ft_strncmp(trim_file, "WE", 2) == 0)
		|| (ft_strncmp(trim_file, "EA", 2) == 0)
		|| (ft_strncmp(trim_file, "NO", 2) == 0)
		|| (ft_strncmp(trim_file, "SO", 2) == 0))
		return (1);
	return (0);
}

int	validating_ceiling_floor(char *trim_file)
{
	if (ft_strncmp(trim_file, "C", 1) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(trim_file, "F", 1) == 0)
	{
		return (1);
	}
	else
		return (0);
}

char	*ft_readfile_content(char *read_file, t_parser *element)
{
	int		fd;
	char	*line_read;
	char	*trim_file;

	fd = ft_open_file(read_file);
	if (fd == 0)
		return (NULL);
	while ((line_read = get_next_line(fd)) != NULL)
	{
		trim_file = ft_skip_whitespace(line_read);
		if (trim_file[0] == '\n')
			continue ;
		if (trim_file == NULL)
			break ;
		if (validating_texture(trim_file))
		{
			if (!checking_texture(trim_file, element))
				break ;
		}
		else if (validating_ceiling_floor(trim_file))
		{
			printf("got here for floor\n");
		}
		// free(trim_file);
		// free (line_read);
	}
	ft_close_error("Invalid map\n", fd);
	return (NULL);
}
