/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:26:06 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/14 01:28:12 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	process_map(char *trim_file, t_parser *element)
{
	if (trim_file[0] == '1' || trim_file[0] == '0')
	{
		if (!validating_map(trim_file, element))
			return (0);
	}
	else
	{
		ft_error("Map out of order\n");
		return (0);
	}
	return (1);
}

static int	process_line(char *trim_file, t_parser *element, int *has_started)
{
	if (*has_started)
		return (process_map(trim_file, element));
	if (validating_texture(trim_file))
	{
		if (!checking_texture(trim_file, element))
			return (0);
	}
	else if (trim_file[0] == 'C' || trim_file[0] == 'F')
	{
		if (!validating_ceiling_floor(trim_file, element))
			return (0);
	}
	else if (trim_file[0] == '1' || trim_file[0] == '0')
	{
		*has_started = 1;
		if (!validating_map(trim_file, element))
			return (0);
	}
	return (1);
}

static int	empty_file(char *trim_file, int *x)
{
	if (trim_file == NULL)
	{
		x = 0;
		return (1);
	}
	return (0);
}

int	read_and_process_lines(int fd, t_parser *element)
{
	char	*trim_file;

	element->x = 0;
	element->has_started = 0;
	element->line_read = get_next_line(fd);
	while (element->line_read != NULL)
	{
		trim_file = ft_skip_check_element_char(element->line_read);
		if (empty_file(trim_file, &element->x))
			return (free(element->line_read), 0);
		if (trim_file[0] == '\n')
		{
			free(element->line_read);
			element->line_read = get_next_line(fd);
			continue ;
		}
		if (!process_line(trim_file, element, & element->has_started))
			return (free(element->line_read), 0);
		element->x = 1;
		free(element->line_read);
		element->line_read = get_next_line(fd);
	}
	return (element->x);
}

int	check_hit(t_player *player, t_game *game)
{
	int	row;
	int	column;

	row = game->element->map_array->max_map_row;
	column = game->element->map_array->max_map_column;
	if (player->map_x >= 0 && player->map_x < row
		&& player->map_y >= 0 && player->map_y < column)
	{
		if (game->map[player->map_y][player->map_x] == '1'
			|| game->map[player->map_y][player->map_x] == ' ')
			return (1);
	}
	return (0);
}
