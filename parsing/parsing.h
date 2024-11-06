/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:20:42 by danevans          #+#    #+#             */
/*   Updated: 2024/11/06 03:19:57 by danevans         ###   ########.fr       */
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
}	t_texture;

typedef struct s_color
{
	int		red;
	int		green;
	int		blue;
}	t_color;

typedef struct s_parser
{
	char		**map;
	t_texture	*texture;
	t_color		*ceiling_color;
	t_color		*floor_color;
}	t_parser;

char	*ft_iswhitespace(char *readfile);

/*parsing.c*/
t_parser	*parsing_func(char *read_file);
int			validate_map(char *read_file, t_parser *element);
int			validate_floor(char *read_file, t_parser *element);
int			validate_ceiling(char *read_file, t_parser *element);

/*texture.c*/
int			validate_south(char *read_file, t_parser *element);
int			validate_north(char *read_file, t_parser *element);
int			validate_east(char *read_file, t_parser *pelement);
int			validate_west(char *read_file, t_parser *element);

/* parsing_utils0.c  */
int			ft_open_file(char *read_file);
int			validating_texture(char *trim_file, t_parser *element);
int			validating_ceiling_floor(char *trim_file, t_parser *element);
int			readfile_and_save_content(char *read_file, t_parser *element);
void		ft_free_trimmed_line_read(char *trim_line, char *line_read);

/* parsing_utils2.c  */
int			checking_texture(char *readfile, t_parser *element);
int			saving_texture(char *readfile, char *texture);
int			num_range(int num, t_color *color);
int			saving_ceiling_and_floor(char *readfile, t_color *color);
int			color_check_pass(t_color *color, char *readfile);

/* utils1.c  */
char		*ft_trim_newline(char *read_file);
int			valid_extension_args_no(char *argv, int ac, char *str);
char		*ft_skip_whitespace(char *file);
void		ft_error(char *msg_error);
void		ft_close_error(char *str, int fd);

#endif