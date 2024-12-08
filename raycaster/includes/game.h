/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:42:14 by ojacobs           #+#    #+#             */
/*   Updated: 2024/12/08 02:35:03 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GAME_H
# define GAME_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define DEBUG 0

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define KEY_ESC 65307
# define PI 3.14159265359

# include "../../mlx/mlx.h"
# include "../../parsing/parsing.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_parser	t_parser;
typedef struct s_map	t_map;
// typedef struct s_texture t_texture;
// typedef struct s_ray t_ray;

// typedef struct s_ray
// {
// 	double	camera_x;
// 	double	dir_x;
// 	double	dir_y;
// 	int		map_x;
// 	int		map_y;
// 	int		step_x;
// 	int		step_y;
// 	double	sidedist_x;
// 	double	sidedist_y;
// 	double	deltadist_x;
// 	double	deltadist_y;
// 	double	wall_dist;
// 	double	wall_x;
// 	int		side;
// 	int		line_height;
// 	int		draw_start;
// 	int		draw_end;
// }	t_ray;


typedef struct s_player
{
	float	x;
	float	y;
	float	player_x;
	float	player_y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;


// typedef struct s_game
// {
//     float ray_dir_x;
//     float ray_dir_y;
//     float delta_dist_x;
//     float delta_dist_y;
//     float side_dist_x;
//     float side_dist_y;
//     int step_x;
//     int step_y;
//     int side; // 0 for vertical wall, 1 for horizontal wall
//     float perp_wall_dist;
//     int line_height;
//     int draw_start;
//     int draw_end;
//     int tex_x;
//     int tex_y;
//     int screen_x;
//     int color;
//     int is_ceiling;
//     t_parser *element;
//     char **map;
//     void *mlx;
//     void *win;
//     void *img;
// 	t_player	player;
// } t_game;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			color;
	int			bpp;
	int			size_line;
	int			endian;
	t_player	player;
	t_parser	*element;
	char		**map;
	int			win_height;
	int			win_width;
	int			**tex_pixels;

	// Add raycasting-related variables
	float ray_dir_x;
    float ray_dir_y;
    float delta_dist_x;
    float delta_dist_y;
    float side_dist_x;
    float side_dist_y;
    int step_x;
    int step_y;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
    int tex_x;
    int tex_y;
    int screen_x;
    float perp_wall_dist;
    int is_ceiling; 
}	t_game;

// typedef struct s_texture
// {
// 	void	*east_img;
// 	void	*west_img;
// 	void	*north_img;
// 	void	*south_img;
// 	int		width;
// 	int		height;
// 	char	*east_data;
// 	char	*west_data;
// 	char	*north_data;
// 	char	*south_data;
// 	int		bpp;
// 	int		size_line;
// 	int		endian;
// }	t_texture;


// void init_player(t_player *player);
int		init_player(t_player *player, t_map *map);
void	init_game(t_game *game, char *argv);
int		key_release(int keycode, t_player *player);
// int 	key_press(int keycode, t_player *player);
int		key_press(int keycode, t_player *player, t_game *game);
// void	move_player(t_player *player);
void	move_player(t_player *player, t_game *game);
bool	touch(float px, float py, t_game *game);
int		draw_loop(t_game *game);
void	put_pixel(int x, int y, t_game *game);
void	clear_image(t_game *game);
void	draw_square(int x, int y, int size, t_game *game);
void	draw_map(t_game *game);
void	load_textures(t_game *game);
void	init_game(t_game *game, char *argv);
// int		get_texture_pixel(t_texture *texture, int x, int y, void *texture_data);
void	init_ray(t_player *player, t_game *game, float ray_angle);
void calculate_step_and_sidedist(t_player *player, t_game *game, t_map *map);
int	perform_dda(t_game *game, t_map *map);
float	calculate_wall_distance(t_player *player, t_game *game, \
 t_map *map, int side);
 void draw_wall(t_game *game);
 void draw_ceiling_floor(t_game *game);
 void draw_ceiling_floor_wall(t_game *game);
//  void draw_line(t_player *player, t_game *game, float ray_angle);
void draw_line(t_player *player, t_game *game, float ray_angle, int screen_x);
 int draw_loop(t_game *game);

#endif