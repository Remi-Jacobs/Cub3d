/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:29:32 by danevans          #+#    #+#             */
/*   Updated: 2024/11/07 21:20:04 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	verify_map_walls_utils(t_parser *element)
{
	int	i;
	int	j;
	int	column;

	i = 0;
	column = element->map_index - 1;
	while (i < column)
	{
		j = 0;
		while (element->map[i][j + 1] != '\0')
			j++;
		if (element->map[i][j] != '1' || element->map[i][0] != '1')
			return (0);
		i++;
	}
}

int	verify_map_walls(t_parser *element)
{
	int	i;
	int	j;
	int	column;

	i = 0;
	column = element->map_index - 1;
	while (element->map[0][i] != '\0')
	{
		if (element->map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (element->map[column][i] != '\0')
	{
		if (element->map[column][i] != '1')
			return (0);
		i++;
	}
	if (!verify_map_walls_utils(element))
		return (0);
	return (1);
}

int	validating_map(char *readfile, t_parser *element)
{
	int		i;
	char	*new_str;
	char	*trim_line;

	i = 0;
	trim_line = ft_trim_newline(readfile);
	new_str = ft_skip_whitespace_map(trim_line);
	while (new_str[i] != '\0')
	{
		if (new_str[i] != '0' && new_str[i] != '1'
			&& new_str[i] != 'N' && new_str[i] != 'W'
			&& new_str[i] != 'S' && new_str[i] != 'E')
		{
			free(new_str);
			free(trim_line);
			ft_error("Invalid map parsed");
			return (0);
		}
		i++;
	}
	element->map[element->map_index++] = ft_strdup(new_str);
	free(new_str);
	free(trim_line);
	return (1);
}

char	*ft_skip_whitespace_map(char *readfile)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	while (readfile[i] != '\0')
	{
		if (!(readfile[i] == ' ' || (readfile[i] >= 9 && readfile[i] <= 13))) 
			j++;
		i++;
	}
	new_str = malloc(sizeof(char) * (j + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (readfile[i] != '\0')
	{
		if (!(readfile[i] == ' ' || (readfile[i] >= 9 && readfile[i] <= 13)))
			new_str[j++] = readfile[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
