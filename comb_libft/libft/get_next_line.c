/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:07:40 by danevans          #+#    #+#             */
/*   Updated: 2024/12/14 01:24:24 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i] != 0)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = 0;
}

int	find_line(char **ret_line, char buff_store[], int *rd_bytes)
{
	char	*linepos;
	int		i;

	i = -1;
	linepos = ft_strchr(buff_store, '\n');
	if (linepos)
	{
		*ret_line = ft_calloc(sizeof(char), (linepos - buff_store) + 2);
		ft_memcpy(*ret_line, buff_store, linepos - buff_store + 1);
		while (linepos[++i + 1] != '\0')
			buff_store[i] = linepos[i + 1];
		ft_bzero(&buff_store[i], MAX_LINE - i);
		return (1);
	}
	if (*rd_bytes == 0)
	{
		*ret_line = ft_calloc(sizeof(char), MAX_LINE + 1);
		ft_memcpy(*ret_line, buff_store, MAX_LINE);
		*rd_bytes = -1;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff_store[MAX_LINE];
	char		*temp_storage;
	char		*ret_line;
	int			rd_bytes;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX_LINE)
		return (NULL);
	temp_storage = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	rd_bytes = read(fd, temp_storage, BUFFER_SIZE);
	ft_strcat(buff_store, temp_storage);
	free(temp_storage);
	if (rd_bytes < 0 || (rd_bytes <= 0 && buff_store[0] == '\0'))
	{
		ft_bzero(buff_store, MAX_LINE);
		return (NULL);
	}
	if (find_line (&ret_line, buff_store, &rd_bytes) == 1)
		return (ret_line);
	if (rd_bytes == -1)
	{
		ft_bzero(buff_store, MAX_LINE);
		return (ret_line);
	}
	return (get_next_line(fd));
}