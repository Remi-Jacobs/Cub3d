/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:29:32 by danevans          #+#    #+#             */
/*   Updated: 2024/12/09 21:51:03 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	element->map_array->max_map_row = get_max_row_length \
	(element->map_array->map, column);
	return (1);
}

// int	verify_map_walls_extra_space(char *map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map[i] != '\0')
// 	{
// 		if (map[i] == ' ' && (map[i + 1] == ' ' || map[i - 1] == ' '))
// 			return (0);
// 		i++;
// 	}
// 	i = 0;
// 	while (map[i] != '\0')
// 	{
// 		if (map[i] == ' ' && (map[i + 1] == ' ' || map[i - 1] == ' '))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

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
