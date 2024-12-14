/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:29:32 by danevans          #+#    #+#             */
/*   Updated: 2024/12/14 00:02:40 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	get_max_row_length(char **map, int column)
{
	int	max_length;
	int	row_length;
	int	i;

	i = 0;
	max_length = 0;
	while (i < column)
	{
		row_length = ft_strlen(map[i]);
		if (row_length > max_length)
			max_length = row_length;
		i++;
	}
	return (max_length);
}

static int	pad_row_len(char **map, int column)
{
	int			i;
	size_t		len;
	size_t		map_len;
	char		*padded_row;

	len = get_max_row_length(map, column);
	i = 0;
	while (map[i] != NULL)
	{
		map_len = ft_strlen(map[i]);
		if (len != map_len)
		{
			padded_row = malloc(len + 1);
			if (!padded_row)
				return (-1);
			ft_memcpy(padded_row, map[i], map_len);
			ft_memset(padded_row + map_len, ' ', len - map_len);
			padded_row[len] = '\0';
			free(map[i]);
			map[i] = padded_row;
		}
		i++;
	}
	return (0);
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
		if (element->map_array->map[i][j] != '1' || \
			element->map_array->map[i][0] != '1')
		{
			ft_error("MAP not surrounded west||east \n");
			return (0);
		}
		i++;
	}
	element->map_array->max_map_column = column + 1;
	element->map_array->max_map_row
		= get_max_row_length(element->map_array->map, column);
	pad_row_len(element->map_array->map, column);
	return (1);
}

int	evaluate_multiple_pos(char **map)
{
	int	flag;
	int	i;
	int	j;

	i = -1;
	flag = 0;
	while (map[++i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N')
				flag++;
			else if (map[i][j] == 'S')
				flag++;
			else if (map[i][j] == 'W')
				flag++;
			else if (map[i][j] == 'E')
				flag++;
			j++;
		}
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	get_player_pos(t_map *map)
{
	int	flag;
	int	i;
	int	j;

	i = 0;
	flag = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'W')
			{
				map->player_column = i;
				map->player_row = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
