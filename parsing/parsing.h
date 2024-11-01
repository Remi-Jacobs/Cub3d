/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:20:42 by danevans          #+#    #+#             */
/*   Updated: 2024/11/01 21:01:57 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../comb_libft/ft_printf.h"

typedef struct s_texture
{
	char	*east;
	char	*west;
	char	*north;
	char	*south;
}t_texture;

typedef struct s_parser
{
	char		**map;
	t_texture	*texture;	
	char		*ceiling;
	char		*floor;
}t_parser;

/*parsing.c*/
int		parsing_func(char *read_file, t_parser *parser);
int		validate_map(char *read_file, t_parser *parser);
int		validate_floor(char *read_file, t_parser *parser);
int		validate_ceiling(char *read_file, t_parser *parser);
int		validate_texture(char *read_file, t_parser *parser);

/*texture.c*/
int		validate_south(char *read_file, t_parser *parser);
int		validate_north(char *read_file, t_parser *parser);
int		validate_east(char *read_file, t_parser *parser);
int		validate_west(char *read_file, t_parser *parser);

int		saving_texture(char *readfile, t_parser *elements);

/* utils.c  */
int		checking_texture(char *readfile, t_parser *element);
char	*ft_readfile_content(char *read_file, t_parser *element);


/* utils1.c  */
char	*ft_trim_newline(char *read_file);
int		valid_extension_args_no(char *argv, int ac, char *str);
char	*ft_skip_whitespace(char *file);
void	ft_error(char *msg_error);
void	ft_close_error(char *str, int fd);

#endif