/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:29:32 by danevans          #+#    #+#             */
/*   Updated: 2024/12/02 15:10:08 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	get_max_row_length(char **map, int column)
{
	int maxLength;
	int rowLength;
	int	i;

	i = 0;
	maxLength = 0;
	while (i < column)
	{
		rowLength = ft_strlen(map[i]);
		if (rowLength > maxLength)
			maxLength = rowLength;
		i++;
	}
	return (maxLength);
}

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
		while (element->map_array->map[i][j + 1] != '\0')
			j++;
		if (element->map_array->map[i][j] != '1' || element->map_array->map[i][0] != '1')
			return (0);
		i++;
	}
	element->map_array->max_map_column = column + 1;
	element->map_array->max_map_row =  get_max_row_length(element->map_array->map, column);
	printf("len_min = %d and max = %d\n" , element->map_array->max_map_column, element->map_array->max_map_row);
	return (1);
}

static int	verify_map_walls_extra_space(char *map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == ' ' && (map[i + 1] == ' ' || map[i - 1] == ' '))
			return (0);
		i++;
	}
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == ' ' && (map[i + 1] == ' ' || map[i - 1] == ' '))
			return (0);
		i++;
	}
	return (1);
}

int	verify_map_walls(t_parser *element)
{
	int	i;
	int	j;
	int	column;

	i = 0;
	column = element->map_index - 1;
	while (element->map_array->map[0][i] != '\0')
	{
		if (element->map_array->map[0][i] != '1'
			&& element->map_array->map[0][i] != ' ')
			return (0);
		if (!verify_map_walls_extra_space(element->map_array->map[0]))
			return (0);
		i++;
	}
	i = 0;
	while (element->map_array->map[column][i] != '\0')
	{
		if (element->map_array->map[column][i] != '1'
			&& element->map_array->map[column][i] != ' ')
			return (0);
		if (!verify_map_walls_extra_space(element->map_array->map[column]))
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
	while (trim_line[i] != '\0')
	{
		if (trim_line[i] != '0' && trim_line[i] != '1'
			&& trim_line[i] != 'N' && trim_line[i] != 'W'
			&& trim_line[i] != 'S' && trim_line[i] != 'E'
			&& trim_line[i] != ' ')
		{
			free(trim_line);
			ft_error("Invalid map parsed");
			return (0);
		}
		i++;
	}
	element->map_array->map[element->map_index++] = ft_strdup(trim_line);
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
