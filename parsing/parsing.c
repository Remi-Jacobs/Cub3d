/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/11/01 20:54:35 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_iswhitespace(char *readfile)
{
	while (*readfile)
	{
		if (*readfile == ' ' || (*readfile >= 9 && *readfile <= 13))
			readfile++;
		else
			break ;
	}
	return ((char *)readfile);
}

void	init_elements(t_parser *element)
{
	element.
}

int	saving_texture(char *readfile, t_parser *elements)
{
	char	*new_trim;

	readfile += 2;
	readfile = ft_iswhitespace(readfile);
	new_trim = ft_trim_newline(readfile);
	if (!valid_extension_args_no(new_trim, 2, "xpm"))
		return (0);
	// save my texture into the struct here before return
	// free new_trim
	printf("checking = %s\n", readfile);
	return (1);
}

int	checking_texture(char *readfile, t_parser *element)
{
	if (ft_strncmp(readfile, "WE", 2) == 0)
	{
		if (saving_texture(readfile, element))
			return (1);
	}
	else if (ft_strncmp(readfile, "EA", 2) == 0)
	{
		if (saving_texture(readfile, element))
			return (1);
	}
	else if (ft_strncmp(readfile, "NO", 2) == 0)
	{
		if (saving_texture(readfile, element))
			return (1);
	}
	else if (ft_strncmp(readfile, "SO", 2) == 0)
	{
		if (saving_texture(readfile, element))
			return (1);
	}
	return (0);
}

int	parsing_func(char *read_file, t_parser *element)
{
	ft_readfile_content(read_file, element);
		printf("all is done \n");
	
	return (1);
}

int	main(int ac, char **argv)
{
	t_parser	parser;

	if (!valid_extension_args_no(argv[1], ac, "cub"))
		return (0);
	parsing_func(argv[1], &parser);
	return (0);
}
