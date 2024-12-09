/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 20:13:41 by danevans          #+#    #+#             */
/*   Updated: 2024/12/09 22:36:26 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	*ft_trim_newline(char *read_file)
{
	int		len;
	char	*trim_str;

	len = ft_strlen(read_file);
	if (read_file[len - 1] == '\n')
	{
		trim_str = malloc(sizeof(char) * len);
		ft_strlcpy(trim_str, read_file, len);
		return (trim_str);
	}
	trim_str = ft_strdup(read_file);
	return (trim_str);
}

int	valid_extension_file_check(char *argv, int ac, char *str)
{
	char	*file;
	int		len;

	if (ac == 2)
	{
		file = argv;
		len = ft_strlen(file) - 4;
		file += len;
		if (*file == '.')
		{
			while (*file)
			{
				file++;
				if ((!ft_strncmp(file, str, 3)) && (ft_strlen(file) == 3))
					return (1);
			}
		}
		ft_error("invalid extension\n");
		return (0);
	}
	ft_error("invalid number of args\n");
	return (0);
}

int	valid_extension_args_no(char *argv, int ac, char *str)
{
	char	*file;

	if (ac == 2)
	{
		file = argv;
		while (*file)
		{
			if (*file == '.')
			{
				file++;
				if (*file == '/')
					continue ;
				if ((!ft_strncmp(file, str, 3)) && (ft_strlen(file) == 3))
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

char	*ft_skip_check_element_char(char *file)
{
	while (*file == ' ' || *file == 9
		|| (*file >= 11 && *file <= 13))
		file++;
	if (*file == 'N' || *file == 'S' || *file == 'W'
		|| *file == 'E' || *file == 'F' || *file == 'C'
		|| *file == '1' ||  *file == '0')
		return (file);
	if (*file == '\n')
		return (file);
	ft_error("Invalid map found from check_element func\n");
	return (NULL);
}

void	ft_error(char *msg_error)
{
	while (*msg_error)
		write (1, msg_error++, 1);
}

// void	ft_close_error(char *str, int fd)
// {
// 	ft_error(str);
// 	close(fd);
// }
