/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:07:40 by danevans          #+#    #+#             */
/*   Updated: 2024/12/09 16:26:37 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	*bytes_read(int fd, char *backup, char *buffer)
// {
// 	char	*temp;
// 	ssize_t	bytes;

// 	bytes = read(fd, buffer, BUFFER_SIZE);
// 	while (bytes > 0)
// 	{
// 		buffer[bytes] = '\0';
// 		if (!backup)
// 			backup = ft_strdup("");
// 		temp = backup;
// 		backup = ft_strjoin(backup, buffer);
// 		free(temp);
// 		if (ft_strchr(backup, '\n'))
// 			break ;
// 		bytes = read(fd, buffer, BUFFER_SIZE);
// 	}
// 	if (bytes == -1)
// 	{
// 		free(buffer);
// 		free(backup);
// 		return (NULL);
// 	}
// 	free(buffer);
// 	return (backup);
// }

// static char	*ft_line(char *backup)
// {
// 	int		count;
// 	char	*line;

// 	if (!backup)
// 		return (NULL);
// 	count = 0;
// 	while (backup[count] != '\0')
// 	{
// 		if (backup[count] == '\n')
// 			break ;
// 		count++;
// 	}
// 	line = malloc(sizeof(char) * (count + 2));
// 	if (!line)
// 		return (NULL);
// 	ft_strlcpy(line, backup, count + 2);
// 	if (line[0] == '\0')
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	return (line);
// }

// static char	*ft_update_backup(char *backup)
// {
// 	int		count;
// 	char	*new_back;

// 	count = 0;
// 	while (backup[count] != '\0')
// 	{
// 		if (backup[count] == '\n')
// 			break ;
// 		count++;
// 	}
// 	if (backup[count] == '\0')
// 	{
// 		free (backup);
// 		return (NULL);
// 	}
// 	new_back = malloc(sizeof(char) * (ft_strlen(backup) - count + 1));
// 	if (!new_back)
// 		return (NULL);
// 	ft_strlcpy(new_back, backup + count + 1, ft_strlen(backup) - count + 1);
// 	free(backup);
// 	return (new_back);
// }

// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	char		*buffer;
// 	static char	*backup;

// 	line = NULL;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buffer = malloc(sizeof (char) * (BUFFER_SIZE + 1));
// 	if (!buffer)
// 	{
// 		free (buffer);
// 		return (NULL);
// 	}
// 	backup = bytes_read(fd, backup, buffer);
// 	if (backup == NULL)
// 		return (NULL);
// 	line = ft_line(backup);
// 	backup = ft_update_backup(backup);
// 	return (line);
// }

static char	*ft_strrrchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_m_strjoin(char *bucket, char *bailer)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!bucket)
	{
		bucket = (char *)malloc(1 * sizeof(char));
		bucket[0] = '\0';
	}
	if (!bucket || !bailer)
		return (NULL);
	str = malloc(((ft_strlen(bucket) + ft_strlen(bailer)) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (bucket)
		while (bucket[++i] != '\0')
			str[i] = bucket[i];
	while (bailer[j] != '\0')
		str[i++] = bailer[j++];
	str[ft_strlen(bucket) + ft_strlen(bailer)] = '\0';
	free(bucket);
	return (str);
}

char	*ft_read_to_bucket(int fd, char *bucket)
{
	int		fd_read;
	char	*bailer;

	bailer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!bailer)
		return (NULL);
	fd_read = 1;
	while (!ft_strrrchr(bucket, '\n') && fd_read != 0)
	{
		fd_read = read(fd, bailer, BUFFER_SIZE);
		if (fd_read == -1)
		{
			free(bailer);
			free(bucket);
			return (NULL);
		}
		bailer[fd_read] = '\0';
		bucket = ft_m_strjoin(bucket, bailer);
	}
	free(bailer);
	return (bucket);
}

char	*ft_get_line(char *bucket)
{
	char	*line;
	int		c;

	c = 0;
	if (!bucket[c])
		return (NULL);
	while (bucket[c] && bucket[c] != '\n')
		c++;
	line = malloc((c + 2) * sizeof(char));
	if (!line)
		return (NULL);
	c = 0;
	while (bucket[c] && bucket[c] != '\n')
	{
		line[c] = bucket[c];
		c++;
	}
	if (bucket[c] == '\n')
	{
		line[c] = bucket[c];
		c++;
	}
	line[c] = '\0';
	return (line);
}

char	*ft_new_bucket(char *bucket)
{
	char	*new_bucket;
	int		c;
	int		c2;

	c = 0;
	while (bucket[c] && bucket[c] != '\n')
		c++;
	if (!bucket[c])
	{
		free(bucket);
		return (NULL);
	}
	new_bucket = malloc((ft_strlen(bucket) - c) * sizeof(char) + 2);
	if (!new_bucket)
		return (NULL);
	c++;
	c2 = 0;
	while (bucket[c])
		new_bucket[c2++] = bucket[c++];
	new_bucket[c2] = '\0';
	free(bucket);
	return (new_bucket);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*bucket;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bucket = ft_read_to_bucket(fd, bucket);
	if (!bucket)
		return (NULL);
	line = ft_get_line(bucket);
	bucket = ft_new_bucket(bucket);
	return (line);
}
