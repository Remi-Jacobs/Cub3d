/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:20:42 by danevans          #+#    #+#             */
/*   Updated: 2024/10/30 00:49:24 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "../comb_libft/ft_printf.h"

typedef struct s_parser
{
	char	**map;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	
}t_parser;


/*parsing.c*/
int	parsing_func(char *read_file, t_parser *parser);
int	validate_map(char *read_file, t_parser *parser);
int	validate_floor(char *read_file, t_parser *parser);
int	validate_ceiling(char *read_file, t_parser *parser);
int	validate_texture(char *read_file, t_parser *parser);

/*texture.c*/
int	validate_south(char *read_file, t_parser *parser);
int	validate_north(char *read_file, t_parser *parser);
int	validate_east(char *read_file, t_parser *parser);
int	validate_west(char *read_file, t_parser *parser);

/* utils.c  */
void	ft_error(char *msg_error);

#endif