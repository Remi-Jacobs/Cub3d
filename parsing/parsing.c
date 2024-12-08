/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/12/08 05:05:39 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	readfile_and_save_content(char *read_file, t_parser *element)
// {
// 	int		fd;
// 	char	*line_read;
// 	char	*trim_file;
// 	int		x;

// 	x = 0;
// 	fd = ft_open_file(read_file);
// 	if (fd == 0)
// 		return (0);
// 	while ((line_read = get_next_line(fd)) != NULL)
// 	{
// 		trim_file = ft_skip_check_element_char(line_read);
// 		if (trim_file == NULL)
// 			break ;
// 		if (trim_file[0] == '\n')
// 			continue ;
// 		if (validating_texture(trim_file, element))
// 		{
// 			if (!checking_texture(trim_file, element))
// 			{
// 				free(trim_file);
// 				return (0);
// 			}
// 			x = 1;
// 		}
// 		else if (trim_file[0] == 'C' || trim_file[0] == 'F')
// 		{
// 			if (!validating_ceiling_floor(trim_file, element))
// 			{
// 				free(trim_file);
// 				return (0);
// 			}
// 			x = 1;
// 		}
// 		else if (trim_file[0] == '1')
// 		{
// 			if (!validating_map(trim_file, element))
// 			{
// 				ft_error("\n\nhere hherehhere Invalid elemenT recieved\n");
// 				free(trim_file);
// 				return (0);
// 			}
// 			x = 1;
// 		}
// 	}
// 	free(line_read);
// 	if (x)
// 		return (1);
// 	ft_error("Invalid elemenT recieved\n");
// 	return (0);
// }

int	process_line(char *trim_file, t_parser *element)
{
	int	result;

	result = 1;
	if (validating_texture(trim_file, element)){	
		printf("ev here\n");
		result = checking_texture(trim_file, element);
	}
	else if (trim_file[0] == 'C' || trim_file[0] == 'F'){		
		printf("after got here\n");
		result = validating_ceiling_floor(trim_file, element);
	}
	else if (trim_file[0] == '1'){
		printf("ever ffff got here\n");
		result = validating_map(trim_file, element);
	}
	printf("error just got here\n");
	if (!result)
	{
		printf("error just got here\n");
		// free(trim_file);
		if (trim_file[0] == '1')
			ft_error("Invalid map element received\n");
		return (0);
	}
	return (1);
}

//i might need your gnl to put in here to see if the leaks can be avoided
int	read_and_process_lines(int fd, t_parser *element)
{
	char	*line_read;
	char	*trim_file;
	int		x;

	x = 0;
	line_read = get_next_line(fd);
	while (line_read != NULL)
	{
		trim_file = ft_skip_check_element_char(line_read);
		if (trim_file == NULL)
			break;
		if (trim_file[0] == '\n')
		{
			line_read = get_next_line(fd);
			continue ;
		}
		if (process_line(trim_file, element))
			x = 1;
		line_read = get_next_line(fd);
		printf("\nhere is mad\n");
	}
	free(line_read);
	return (x);
}

int	readfile_and_save_content(char *read_file, t_parser *element)
{
	int		fd;
	int		x;

	fd = ft_open_file(read_file);
	if (fd == 0)
		return (0);
	x = read_and_process_lines(fd, element);
	if (x)
		return (1);
	ft_error("Invalid element received\n");
	return (0);
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
		printf("\nbad here\n\n\n");
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
