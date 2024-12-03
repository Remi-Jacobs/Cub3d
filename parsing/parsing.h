/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:20:42 by danevans          #+#    #+#             */
/*   Updated: 2024/12/03 02:25:55 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../comb_libft/ft_printf.h"
# include "../mlx/mlx.h"
# include "../raycaster/includes/game.h"

# define MAP_HEIGHT 20
# define TILE_SIZE 60
# define TILE_SIZE_MINI 20
# define IMAGE "./wall.xpm"

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

// typedef struct s_player
// {
// 	double		player_posX;
// 	double		player_posY;
	
// }	t_player;

typedef struct s_map
{
	char		**map;
	int			player_row;
	int			player_column;
	int			max_map_row;
	int 		max_map_column;
	
}	t_map;

typedef struct s_parser
{
	int			map_index;
	t_map		*map_array;
	t_texture	*texture;
	t_color		*ceiling_color;
	t_color		*floor_color;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image;
}	t_parser;

int	valid_extension_file_check(char *argv, int ac, char *str);

/*parsing_init.c    file full and formatted */
t_parser	*init_elements(void);
int			init_ceil_floor_color(t_parser *element);
void		init_texture_maps(t_parser *element);
void		free_map_stored(t_parser *element);
void		free_parser_struct(t_parser *element);

/*parsing_map_check.c    file full and formatted */
int			verify_map_walls_utils(t_parser *element);
int			verify_map_walls(t_parser *element);
int			validating_map(char *readfile, t_parser *element);
char		*ft_skip_whitespace_map(char *readfile);

/* parsing_utils0.c  */
int			ft_open_file(char *read_file);
int			validating_texture(char *trim_file, t_parser *element);
int			validating_ceiling_floor(char *trim_file, t_parser *element);
char		*ft_iswhitespace(char *readfile);
void		ft_free_trimmed_line_read(char *trim_line, char *line_read);

/* parsing_utils1.c  */
char		*ft_trim_newline(char *read_file);
int			valid_extension_args_no(char *argv, int ac, char *str);
char		*ft_skip_check_element_char(char *file);
void		ft_error(char *msg_error);
void		ft_close_error(char *str, int fd);

/* parsing_utils2.c  */
int			checking_texture(char *readfile, t_parser *element);
int			saving_texture(char *readfile, char **texture);
int			num_range(int num, t_color *color);
int			saving_ceiling_and_floor(char *readfile, t_color *color);
int			color_check_pass(t_color *color, char *readfile);

/*parsing.c*/
int			readfile_and_save_content(char *read_file, t_parser *element);
t_parser	*parsing_func(char *read_file);
#endif