/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:30:12 by danevans          #+#    #+#             */
/*   Updated: 2024/12/13 18:02:24 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	set_player_angle(t_map *map, t_player *player)
{
	if (map->map[map->player_column][map->player_row] == 'N')
		player->angle = 3 * PI / 2;
	else if (map->map[map->player_column][map->player_row] == 'S')
		player->angle = PI / 2;
	else if (map->map[map->player_column][map->player_row] == 'E')
		player->angle = 0;
	else if (map->map[map->player_column][map->player_row] == 'W')
		player->angle = PI;
	else
	{
		ft_error("ERROR: Need a position to start\n");
		return (0);
	}
	return (1);
}

bool	touch(float px, float py, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(px / BLOCK);
	map_y = (int)(py / BLOCK);
	if (map_x < 0 || map_x >= game->element->map_array->max_map_row
		|| map_y < 0 || map_y >= game->element->map_array->max_map_column)
		return (true);
	if (game->map[map_y][map_x] == '1' || game->map[map_y][map_x] == ' ')
	{
		printf("Collision at: map_x=%d, map_y=%d\n", map_x, map_y);
		return (true);
	}

	return (false);
}

int	init_player(t_player *player, t_map *map)
{
	player->player_x = map->player_row * BLOCK + BLOCK / 2;
	player->player_y = map->player_column * BLOCK + BLOCK / 2;
	if (map->map[map->player_column][map->player_row] == '1'
		||map->map[map->player_column][map->player_row] == ' ')
	{
		ft_error("ERROR: Player starting pos inside wall or out of bounds\n");
		return (0);
	}
	if (!set_player_angle(map, player))
		return (0);
	player->key_up = false;
	player->key_down = false;
	player->key_right = false;
	player->key_left = false;
	player->left_rotate = false;
	player->right_rotate = false;
	return (1);
}

void	move_in_direction(t_player *player, t_game *game, int direction)
{
	float	new_x;
	float	new_y;

	if (direction == 1)
	{
		new_x = player->player_x + player->cos_angle * player->speed;
		new_y = player->player_y + player->sin_angle * player->speed;
	}
	else if (direction == -1)
	{
		new_x = player->player_x - player->cos_angle * player->speed;
		new_y = player->player_y - player->sin_angle * player->speed;
	}
	else if (direction == 2)
	{
		new_x = player->player_x + player->sin_angle * player->speed;
		new_y = player->player_y - player->cos_angle * player->speed;
	}
	else if (direction == -2)
	{
		new_x = player->player_x - player->sin_angle * player->speed;
		new_y = player->player_y + player->cos_angle * player->speed;
	}
	if (!touch(new_x, player->player_y, game))
		player->player_x = new_x;
	if (!touch(player->player_x, new_y, game))
		player->player_y = new_y;
}

void	rotate_player(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.03;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	move_player(t_player *player, t_game *game)
{
	player->speed = 5;
	player->sin_angle = sin(player->angle);
	player->cos_angle = cos(player->angle);
	rotate_player(player);
	if (player->key_up)
		move_in_direction(player, game, 1);
	if (player->key_down)
		move_in_direction(player, game, -1);
	if (player->key_left)
		move_in_direction(player, game, 2);
	if (player->key_right)
		move_in_direction(player, game, -2);
}
