#ifndef GAME_H
#define GAME_H

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

#include "./mlx/mlx.h"
#include "../../parsing/parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct s_parser t_parser;
typedef struct s_map t_map;
// typedef struct s_ray t_ray;


typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;


typedef struct s_player
{
    float x;
    float y;

    float       player_dirX;
    float       player_dirY;
    float		player_planeX;
    float		player_planeY;

	float playerX;
	float playerY;
    float angle;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;

    bool left_rotate;
    bool right_rotate;
}   t_player;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;

    char *data;
	int		color;
    int bpp;
    int size_line;
    int endian;
    t_player player;
	t_parser *element;

    char **map;

	t_ray		ray;
	int		win_height;
	int		win_width;
	int		**tex_pixels;

} t_game;


// void init_player(t_player *player);
int		init_player(t_player *player, t_map *map);
void	init_game(t_game *game, char *argv);
int 	key_release(int keycode, t_player *player);
// int 	key_press(int keycode, t_player *player);
int key_press(int keycode, t_player *player, t_game *game);
// void	move_player(t_player *player);
void move_player(t_player *player, t_game *game);
bool touch(float px, float py, t_game *game);
int		draw_loop(t_game *game);

# endif