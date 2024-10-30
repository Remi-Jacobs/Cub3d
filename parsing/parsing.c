/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/10/30 18:34:20 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *extract_line_needed(char *readfile, int i)
{
	char *file_extracted;

	file_extracted = NULL;
	if (i == 'W')
		file_extracted = file_open_and_read_content(readfile, 'W');
	else if (i == 'E')	
		file_extracted = file_open_and_read_content(readfile, 'E');
	else if (i == 'S')
		file_extracted = file_open_and_read_content(readfile, 'S');
	else if (i == 'N')
		file_extracted = file_open_and_read_content(readfile, 'N');
	else if (i == 'C')
		file_extracted = file_open_and_read_content(readfile, 'C');
	else if (i == 'F')
		file_extracted = file_open_and_read_content(readfile, 'F');
	else if (i == '1')
		file_extracted = file_open_and_read_content(readfile, '1');
	else
		ft_error("Invalid map parsed");
	return (file_extracted);
}

int	parsing_func(char *read_file, t_parser *parser)
{
	
	if (validate_texture((read_file), parser))
	{
		printf("got all all texture\n");
	}
	if (validate_floor((read_file), parser))
	{
		printf("got the floor\n");
	}
	if (validate_ceiling((read_file), parser))
	{
		printf("got the ceiling\n");
	}
	if (!validate_map((read_file), parser))
		return (0);
	return (1);
}

int	validate_map(char *read_file, t_parser *parser)
{
	return (1);
}

int	validate_floor(char *read_file, t_parser *parser)
{
	char	*floor;

	floor = extract_line_needed(read_file, 'F');
	if (floor == NULL)
		return (0);
	printf("floor = %s\n", floor);
	return (1);
}

int	validate_ceiling(char *read_file, t_parser *parser)
{
	char	*ceiling;

	ceiling = extract_line_needed(read_file, 'C');
	printf("ceiling = %s\n", ceiling );
	if (ceiling == NULL)
		return (0);	
	return (1);
}

int	validate_texture(char *read_file, t_parser *parser)
{
	char	*east;
	char	*west;
	char	*north;
	char	*south;

	east = extract_line_needed(read_file, 'E');
	west = extract_line_needed(read_file, 'W');
	north = extract_line_needed(read_file, 'N');
	south = extract_line_needed(read_file, 'S');
	if (east == NULL && west == NULL && south == NULL && north == NULL)
	{
		ft_error("Invalid Texture\n");
		return (0);
	}
	printf("east = %s\n", east);
	printf("west = %s\n", west);
	printf("north = %s\n", north);
	printf("south = %s\n", south);
	return (1);	
}

int main(int ac, char **argv)
{
	t_parser parser;
	if (!valid_extension_args_no(argv, ac))
		return (0);
	parsing_func(argv[1], &parser);
	return (0);
	
}