/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/11/06 01:10:16 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_parser	*parsing_func(char *read_file)
{
	t_parser	*element;

	element = init_elements();
	if (!readfile_and_save_content(read_file, element))
	{
		/*delete and free the element struct */		
		return (NULL);
	}
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
	return (0);
}

t_parser	*init_elements(void)
{
	// element->texture. = malloc (si)
}

void	free_parser_struct(t_parser *parser)
{
	//fre all element here
}

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
