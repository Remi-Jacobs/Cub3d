/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:45:41 by danevans          #+#    #+#             */
/*   Updated: 2024/10/30 01:30:31 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


void	ft_error(char *msg_error)
{
	while (*msg_error)
		write (1, msg_error++, 1);
}

char *file_open(char *read_file)
{
	int	fd;
	char *line_read;
	fd = open(read_file, O_RDONLY);
	if (fd == -1)
	{
		ft_error("OPEN failed\n");
		return (NULL);
	}
	line_read = get_next_line(fd);
	if (line_read == NULL)
	{
		ft_error("READ failed\n");
		return (NULL);	
	}
	printf("line = %s\n", line_read);
}