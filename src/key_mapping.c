/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojacobs <ojacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:14:16 by danevans          #+#    #+#             */
/*   Updated: 2024/12/14 01:30:44 by ojacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	if (keycode == KEY_ESC)
		close_game_on_cross(game);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	free_game_struct(t_game *game)
{
	close_game(game);
	if (game->element)
	{
		free_parser_struct(game->element);
		game->element = NULL;
	}
}

int	close_game_on_cross(t_game *game)
{
	free_game_struct(game);
	exit(0);
}

int	close_game(t_game *game)
{
	if (game->element->texture->east->img)
		mlx_destroy_image(game->mlx, game->element->texture->east->img);
	if (game->element->texture->west->img)
		mlx_destroy_image(game->mlx, game->element->texture->west->img);
	if (game->element->texture->south->img)
		mlx_destroy_image(game->mlx, game->element->texture->south->img);
	if (game->element->texture->north->img)
		mlx_destroy_image(game->mlx, game->element->texture->north->img);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	game->win = NULL;
	return (0);
}
