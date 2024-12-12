/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 22:17:17 by danevans          #+#    #+#             */
/*   Updated: 2024/12/11 11:23:43 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "../includes/game.h"

// int	set_player_angle(t_map *map, t_player *player)
// {
// 	if (map->map[map->player_column][map->player_row] == 'N')
// 		player->angle = 3 * PI / 2;
// 	else if (map->map[map->player_column][map->player_row] == 'S')
// 		player->angle = PI / 2;
// 	else if (map->map[map->player_column][map->player_row] == 'E')
// 		player->angle = 0;
// 	else if (map->map[map->player_column][map->player_row] == 'W')
// 		player->angle = PI;
// 	else
// 	{
// 		ft_error("ERROR: Need a position to start\n");
// 		return (0);
// 	}
// 	return (1);
// }

// int	init_player(t_player *player, t_map *map)
// {
// 	player->player_x = map->player_row * BLOCK + BLOCK / 2;
// 	player->player_y = map->player_column * BLOCK + BLOCK / 2;
// 	if (!set_player_angle(map, player))
// 		return (0);
// 	player->key_up = false;
// 	player->key_down = false;
// 	player->key_right = false;
// 	player->key_left = false;
// 	player->left_rotate = false;
// 	player->right_rotate = false;
// 	return (1);
// }

// void move_in_direction(float cos_angle, float sin_angle, int speed, t_player *player, t_game *game, int direction)
// {
// 	float new_x, new_y;

// 	if (direction == 1) // Forward (key_up)
// 	{
// 		new_x = player->player_x + cos_angle * speed;
// 		new_y = player->player_y + sin_angle * speed;
// 	}
// 	else if (direction == -1) // Backward (key_down)
// 	{
// 		new_x = player->player_x - cos_angle * speed;
// 		new_y = player->player_y - sin_angle * speed;
// 	}
// 	else if (direction == 2) // Left (key_left)
// 	{
// 		new_x = player->player_x + sin_angle * speed;
// 		new_y = player->player_y - cos_angle * speed;
// 	}
// 	else if (direction == -2) // Right (key_right)
// 	{
// 		new_x = player->player_x - sin_angle * speed;
// 		new_y = player->player_y + cos_angle * speed;
// 	}

// 	if (!touch(new_x, player->player_y, game))
// 		player->player_x = new_x;
// 	if (!touch(player->player_x, new_y, game))
// 		player->player_y = new_y;
// }

// void rotate_player(t_player *player)
// {
// 	float angle_speed = 0.03;

// 	if (player->left_rotate)
// 		player->angle -= angle_speed;
// 	if (player->right_rotate)
// 		player->angle += angle_speed;

// 	if (player->angle > 2 * PI)
// 		player->angle -= 2 * PI;
// 	if (player->angle < 0)
// 		player->angle += 2 * PI;
// }

// void move_in_direction(float cos_angle, float sin_angle, int speed, t_player *player, t_game *game, int direction)
// {
// 	float new_x, new_y;

// 	if (direction == 1) // Forward (key_up)
// 	{
// 		new_x = player->player_x + cos_angle * speed;
// 		new_y = player->player_y + sin_angle * speed;
// 	}
// 	else if (direction == -1) // Backward (key_down)
// 	{
// 		new_x = player->player_x - cos_angle * speed;
// 		new_y = player->player_y - sin_angle * speed;
// 	}
// 	else if (direction == 2) // Left (key_left)
// 	{
// 		new_x = player->player_x + sin_angle * speed;
// 		new_y = player->player_y - cos_angle * speed;
// 	}
// 	else if (direction == -2) // Right (key_right)
// 	{
// 		new_x = player->player_x - sin_angle * speed;
// 		new_y = player->player_y + cos_angle * speed;
// 	}

// 	if (!touch(new_x, player->player_y, game))
// 		player->player_x = new_x;
// 	if (!touch(player->player_x, new_y, game))
// 		player->player_y = new_y;
// }

// void rotate_player(t_player *player)
// {
// 	float	angle_speed;

// 	angle_speed = 0.03;
// 	if (player->left_rotate)
// 		player->angle -= angle_speed;
// 	if (player->right_rotate)
// 		player->angle += angle_speed;
// 	if (player->angle > 2 * PI)
// 		player->angle -= 2 * PI;
// 	if (player->angle < 0)
// 		player->angle += 2 * PI;
// }

// void move_player(t_player *player, t_game *game)
// {
// 	int speed = 3;
// 	float cos_angle = cos(player->angle);
// 	float sin_angle = sin(player->angle);

// 	rotate_player(player);

// 	if (player->key_up)
// 		move_in_direction(cos_angle, sin_angle, speed, player, game, 1);
// 	if (player->key_down)
// 		move_in_direction(cos_angle, sin_angle, speed, player, game, -1);
// 	if (player->key_left)
// 		move_in_direction(cos_angle, sin_angle, speed, player, game, 2);
// 	if (player->key_right)
// 		move_in_direction(cos_angle, sin_angle, speed, player, game, -2);
// }
