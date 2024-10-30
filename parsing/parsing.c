/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:21:26 by danevans          #+#    #+#             */
/*   Updated: 2024/10/30 01:32:17 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing_func(char *read_file, t_parser *parser)
{
	file_open(read_file);
	if (!validate_texture((read_file), parser))
		return (0);
	if (!validate_floor((read_file), parser))
		return (0);
	if (!validate_ceiling((read_file), parser))
		return (0);
	if (!validate_texture((read_file), parser))
		return (0);
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
	return (1);	
}

int	validate_ceiling(char *read_file, t_parser *parser)
{
	return (1);	
}

int	validate_texture(char *read_file, t_parser *parser)
{
	return (1);	
}

int main(int ac, char **argv)
{
	t_parser parser;
	if (ac != 2)
		ft_error("invalid number of args\n");
	parsing_func(argv[1], &parser);	
}