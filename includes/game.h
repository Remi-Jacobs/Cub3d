/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:42:14 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/14 15:16:48 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../mlx/mlx.h"
# include "./parsing.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define KEY_ESC 65307
# define PI 3.14159265359

typedef struct s_parser		t_parser;
typedef struct s_texture	t_texture;
typedef struct s_map		t_map;
typedef struct s_img_info	t_img_info;
typedef struct s_player
{
	float		x;
	float		y;
	int			map_x;
	int			map_y;
	float		new_x;
	float		new_y;
	float		player_x;
	float		player_y;
	float		angle;
	int			speed;
	float		cos_angle;
	float		sin_angle;
	bool		key_up;
	bool		key_down;
	bool		key_left;
	bool		key_right;
	bool		left_rotate;
	bool		right_rotate;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			color;
	int			bpp;
	int			size_line;
	int			tmp_size_line;
	int			endian;
	char		**map;
	int			**tex_pixels;
	int			win_height;
	int			win_width;
	int			hit;
	float		ray_dir_x;
	float		ray_dir_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		side_dist_x;
	float		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			tex_y;
	int			screen_x;
	float		perp_wall_dist;
	t_player	player;
	t_parser	*element;
}	t_game;

/*	key_mapping.c	*/
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_player *player);
int		close_game_on_cross(t_game *game);
int		close_game(t_game *game);
void	free_game_struct(t_game *game);

/*	ray_caster.c */
void	drawing_ceiling_floor(t_game *game, int screen_x);
void	init_ray_pos(t_player *player, t_game *game, float ray_angle);
void	draw_map_walls(t_game *game, int side, int screen_x);
void	draw_lines(t_player *player, t_game *game,
			float ray_angle, int screen_x);
int		draw_loops(t_game *game);

/*	ray_caster1.c */
int		gtex_pixel(t_img_info *texture, int x, int y, void *texture_data);
int		load_textures(t_game *game);
void	cal_step_and_sidedist(t_player *player, t_game *game);
void	performing_dda(t_player *player, t_game *game, int *side);
float	cal_wall_dist(t_player *player, t_game *game,
			float ray_angle, int side);

/*	ray_caster_utils.c	*/
void	put_pixel(int x, int y, t_game *game);
void	clear_image(t_game *game);
void	init_all(t_game *game);
int		are_dimensions_equal(int h1, int h2, int h3, int h4);
int		ft_image_error(t_texture *texture);

/*	ray_caster_utils.c	*/
void	assign_game_tex(t_game *game);
void	free_image_data(t_img_info *texture);
void	free_img_struct(t_texture *tex);

/*	play_move.c	*/
int		set_player_angle(t_map *map, t_player *player);
bool	touch(float px, float py, t_game *game);
void	move_in_direction(t_player *player, t_game *game, int direction);
void	rotate_player(t_player *player);
void	move_player(t_player *player, t_game *game);

/*	mainc.c	*/
int		init_player(t_player *player, t_map *map);
int		init_game(t_game *game, char *argv);
void	init_game_utils(t_game *game);

#endif