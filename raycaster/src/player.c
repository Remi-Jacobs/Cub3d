
#include "../includes/game.h"

int set_player_angle(t_map *map, t_player *player)
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

int init_player(t_player *player, t_map *map)
{
    player->playerX = map->player_row * BLOCK + BLOCK / 2;
    player->playerY = map->player_column * BLOCK + BLOCK / 2;
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

int key_press(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = true;
    if (keycode == S)
        player->key_down = true;
    if (keycode == A)
        player->key_left = true;
    if (keycode == D)
        player->key_right = true;
    if (keycode == LEFT)
        player->left_rotate = true;
    if (keycode == RIGHT)
        player->right_rotate = true;
    return (0);
}

int key_release(int keycode, t_player *player)
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
    return 0;
}

void move_player(t_player *player, t_game *game)
{
    int speed = 3;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;

    // Collision detection for all directions
    if (player->key_up)
    {
        float new_x = player->playerX + cos_angle * speed;
        float new_y = player->playerY + sin_angle * speed;
        if (!touch(new_x, player->playerY, game))
            player->playerX = new_x;
        if (!touch(player->playerX, new_y, game))
            player->playerY = new_y;
    }
    if (player->key_down)
    {
        float new_x = player->playerX - cos_angle * speed;
        float new_y = player->playerY - sin_angle * speed;
        if (!touch(new_x, player->playerY, game))
            player->playerX = new_x;
        if (!touch(player->playerX, new_y, game))
            player->playerY = new_y;
    }
    if (player->key_left)
    {
        float new_x = player->playerX + sin_angle * speed;
        float new_y = player->playerY - cos_angle * speed;
        if (!touch(new_x, player->playerY, game))
            player->playerX = new_x;
        if (!touch(player->playerX, new_y, game))
            player->playerY = new_y;
    }
    if (player->key_right)
    {
        float new_x = player->playerX - sin_angle * speed;
        float new_y = player->playerY + cos_angle * speed;
        if (!touch(new_x, player->playerY, game))
            player->playerX = new_x;
        if (!touch(player->playerX, new_y, game))
            player->playerY = new_y;
    }
}
