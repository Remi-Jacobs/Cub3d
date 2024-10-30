/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:45:41 by danevans          #+#    #+#             */
/*   Updated: 2024/10/30 18:33:47 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_error(char *msg_error)
{
	while (*msg_error)
		write (1, msg_error++, 1);
}

char	*ft_skip_whitespace(char *file)
{
	while (*file)
	{
		if (*file == 'N' || *file == 'S' || *file == 'W' || *file == 'E'
			|| *file == 'F' || *file == 'C' || *file == '1')
			return ((char *)file);
		file++;
	}
	return (NULL);
}

char	*file_open_and_read_content(char *read_file, char i)
{
	int		fd;
	char	*line_read;
	char	*file;

	fd = open(read_file, O_RDONLY);
	if (fd == -1)
	{
		ft_error("OPEN failed\n");
		return (NULL);
	}
	while ((line_read = get_next_line(fd)) != NULL)
	{
		line_read = ft_skip_whitespace(line_read);
		if (line_read == NULL)
			break ;
		if (line_read[0] == i)
		{
			close(fd);
			printf("from gnl = %s\n", line_read);
			return (line_read);
		}
	}
	ft_error("Invalid map ???\n");
	close(fd);
	return (NULL);
}

int	valid_extension_args_no(char **argv, int ac)
{
	char	*file;

	if (ac == 2)
	{
		file = argv[1];
		while (*file)
		{
			if (*file == '.')
			{
				file++;
				if ((!ft_strncmp(file, "cub", 3)) && (ft_strlen(file) == 3))
					return (1);
				ft_error("invalid extension\n");
				return (0);
			}
			file++;
		}
		ft_error("invalid extension\n");
		return (0);
	}
	ft_error("invalid number of args\n");
	return (0);
}
