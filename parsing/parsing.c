/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/11/07 21:31:49 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	readfile_and_save_content(char *read_file, t_parser *element)
{
	int		fd;
	char	*line_read;
	char	*trim_file;

	fd = ft_open_file(read_file);
	if (fd == 0)
		return (0);
	while ((line_read = get_next_line(fd)) != NULL)
	{
		trim_file = ft_skip_check_element_char(line_read);
		if (trim_file == NULL)
			break ;
		if (trim_file[0] == '\n')
			continue ;
		if (validating_texture(trim_file, element))
		{
			if (!checking_texture(trim_file, element))
				return (0);
		}
		else if (trim_file[0] == 'C' || trim_file[0] == 'F')
		{
			if (!validating_ceiling_floor(trim_file, element))
				return (0);
		}
		else if (trim_file[0] == '1')
		{
			if (!validating_map(trim_file, element))
				return (0);
		}
		// else
		// 	break ;
		// ft_free_trimmed_line_read(trim_file, line_read);	
	}
	free(line_read);
	ft_error("Invalid elementfghfghfgh recieved\n");
	// ft_free_trimmed_line_read(trim_file, line_read);
	return (1);
}

t_parser	*parsing_func(char *read_file)
{
	t_parser	*element;

	element = init_elements();
	if (element == NULL)
		return (NULL);
	printf("1 .....successffully got here\n\n\n");
	if (!readfile_and_save_content(read_file, element))
	{
		free_parser_struct(element);
		return (NULL);
	}
	printf("2.....successffully got here\n\n\n");
	if (!verify_map_walls(element))
	{
		printf("errror here\n\n\n");
		free_parser_struct(element);
		return (NULL);
	}
	printf("3 ...successffully got here\n\n\n");
	return (element);
}

int	main(int ac, char **argv)
{
	t_parser	*parser;

	if (!valid_extension_args_no(argv[1], ac, "cub"))
		return (0);
	parser = parsing_func(argv[1]);
	if (parser == NULL)
		return (0);
	// printf("red = '%d' ", parser->ceiling_color->red);
	// printf("green = '%d' ", parser->ceiling_color->green);
	// printf("blue = '%d' ", parser->ceiling_color->blue);
	free_parser_struct(parser);
	printf("final arrivall success\n");
	return (0);
}