/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_check2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:48:15 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/13 16:52:36 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	verify_top_wall(t_parser *element)
{
	int	i;

	i = 0;
	if (element->map_array->map[0] == NULL)
	{
		ft_error("MAP not found\n");
		return (0);
	}
	while (element->map_array->map[0][i] != '\0')
	{
		if (element->map_array->map[0][i] != '1' && \
			element->map_array->map[0][i] != ' ')
		{
			ft_error("MAP not surrounded by wall at the top\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	verify_bottom_wall(t_parser *element)
{
	int	i;
	int	column;

	i = 0;
	column = element->map_index - 1;
	while (element->map_array->map[column][i] != '\0')
	{
		if (element->map_array->map[column][i] != '1' && \
			element->map_array->map[column][i] != ' ')
		{
			ft_error("MAP not surrounded by wall at the bottom\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	verify_map_walls(t_parser *element)
{
	if (!verify_top_wall(element))
		return (0);
	if (!verify_bottom_wall(element))
		return (0);
	if (!verify_map_walls_utils(element))
		return (0);
	if (!evaluate_multiple_pos(element->map_array->map))
	{
		ft_error("Multiple player positions found\n");
		return (0);
	}
	if (!get_player_pos(element->map_array))
	{
		ft_error("Couldn't determine player position\n");
		return (0);
	}
	return (1);
}

int	validating_map(char *readfile, t_parser *element)
{
	int		i;
	char	*trim_line;

	i = 0;
	trim_line = ft_trim_newline(readfile);
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
