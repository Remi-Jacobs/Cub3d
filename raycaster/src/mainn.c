#include "../includes/game.h"

// our own put_pixel

void put_pixel(int x, int y, int color, t_game *game)
{
    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    
    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}

// our own clear_image
void clear_image(t_game *game)
{
    for(int y = 0; y < HEIGHT; y++)
        for(int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, game);
}

// utils functions
void draw_square(int x, int y, int size, int color, t_game *game)
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}

void draw_map(t_game *game)
{
    char **map = game->map;
    int color = 0xFF0000;
    for(int y = 0; map[y]; y++)
        for(int x = 0; map[y][x]; x++)
            if(map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

// distance calculation functions
float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;

    // Correct for fish-eye effect
    float raw_dist = distance(delta_x, delta_y);
    return raw_dist * cos(angle);
}


// float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
// {
//     float delta_x = x2 - x1;
//     float delta_y = y2 - y1;
//     float angle = atan2(delta_y, delta_x) - game->player.angle;
//     float fix_dist = distance(delta_x, delta_y) * cos(angle);
//     return fix_dist;
// }

// touch function 
bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
    int y = py / BLOCK;
    if(game->map[y][x] == '1' || game->map[y][x] == ' ')
        return true;
    return false;
}

void load_textures(t_game *game)
{
    // Load East texture
    game->element->texture->east_img = mlx_xpm_file_to_image(game->mlx, "./Tower_Blue.xpm", &game->element->texture->width, &game->element->texture->height);
    game->element->texture->east_data = mlx_get_data_addr(game->element->texture->east_img, &game->element->texture->bpp, &game->element->texture->size_line, &game->element->texture->endian);

    // Load West texture
    game->element->texture->west_img = mlx_xpm_file_to_image(game->mlx, "./Tower_Red.xpm", &game->element->texture->width, &game->element->texture->height);
    game->element->texture->west_data = mlx_get_data_addr(game->element->texture->west_img, &game->element->texture->bpp, &game->element->texture->size_line, &game->element->texture->endian);

    // Load North texture
    game->element->texture->north_img = mlx_xpm_file_to_image(game->mlx, "./Gate_Closed.xpm", &game->element->texture->width, &game->element->texture->height);
    game->element->texture->north_data = mlx_get_data_addr(game->element->texture->north_img, &game->element->texture->bpp, &game->element->texture->size_line, &game->element->texture->endian);

    // Load South texture
    game->element->texture->south_img = mlx_xpm_file_to_image(game->mlx, "./Mushroom.xpm", &game->element->texture->width, &game->element->texture->height);
    game->element->texture->south_data = mlx_get_data_addr(game->element->texture->south_img, &game->element->texture->bpp, &game->element->texture->size_line, &game->element->texture->endian);
}

// initialisation functions

void init_game(t_game *game, char *argv)
{
	game->element = parsing_func(argv);
    if (game->element == NULL)
        return;
    init_player(&game->player, game->element->map_array);
    game->map = game->element->map_array->map;
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
    load_textures(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int get_texture_pixel(void *texture_data, int x, int y, int size_line, int bpp)
{
    int offset = (y * size_line + x * (bpp / 8));  // Calculate the pixel offset
    unsigned char *data = (unsigned char *)texture_data;
    int color = (*(int *)(data + offset));  // Extract the pixel color
    return color;
}

void draw_line(t_player *player, t_game *game, float ray_angle, int screen_x)
{
    float cos_angle = cos(ray_angle);
    float sin_angle = sin(ray_angle);

    float ray_x = player->playerX;
    float ray_y = player->playerY;

    int texture_direction = 0; // 0 = east, 1 = west, 2 = north, 3 = south
    int hit_vertical = 0;      // 1 = vertical hit, 0 = horizontal hit

    float delta_dist_x = fabs(1 / cos_angle);
    float delta_dist_y = fabs(1 / sin_angle);

    float step_x = (cos_angle > 0) ? 1 : -1;
    float step_y = (sin_angle > 0) ? 1 : -1;

    float side_dist_x = (cos_angle > 0) ? 
        (floor(ray_x / BLOCK) * BLOCK + BLOCK - ray_x) * delta_dist_x :
        (ray_x - floor(ray_x / BLOCK) * BLOCK) * delta_dist_x;

    float side_dist_y = (sin_angle > 0) ? 
        (floor(ray_y / BLOCK) * BLOCK + BLOCK - ray_y) * delta_dist_y :
        (ray_y - floor(ray_y / BLOCK) * BLOCK) * delta_dist_y;

    while (!touch(ray_x, ray_y, game))
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            ray_x += step_x;
            ray_y += step_x * sin_angle / cos_angle;
            hit_vertical = 1;
            texture_direction = (cos_angle > 0) ? 0 : 1;
        }
        else
        {
            side_dist_y += delta_dist_y;
            ray_y += step_y;
            ray_x += step_y * cos_angle / sin_angle;
            hit_vertical = 0;
            texture_direction = (sin_angle > 0) ? 3 : 2;
        }
    }

    float dist = fixed_dist(player->playerX, player->playerY, ray_x, ray_y, game);
    dist = fabs(dist); // Ensure the distance is always positive

    float height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;

    if (start_y < 0) start_y = 0;
    if (end >= HEIGHT) end = HEIGHT - 1;

    for (int y = 0; y < start_y; y++)
        put_pixel(screen_x, y, game->element->ceiling_color->converted_color, game);

    while (start_y < end)
    {
        int tex_y = (start_y - (HEIGHT - height) / 2) * game->element->texture->height / height;
        tex_y = tex_y < 0 ? 0 : tex_y;
        tex_y = tex_y >= game->element->texture->height ? game->element->texture->height - 1 : tex_y;

        int tex_x = hit_vertical ? ((int)ray_y % BLOCK) : ((int)ray_x % BLOCK);
        tex_x = (tex_x * game->element->texture->width) / BLOCK;
        tex_x = tex_x < 0 ? 0 : tex_x;
        tex_x = tex_x >= game->element->texture->width ? game->element->texture->width - 1 : tex_x;

        int tex_color = 0;
        if (texture_direction == 0)
            tex_color = get_texture_pixel(game->element->texture->east_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
        else if (texture_direction == 1)
            tex_color = get_texture_pixel(game->element->texture->west_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
        else if (texture_direction == 2)
            tex_color = get_texture_pixel(game->element->texture->north_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
        else if (texture_direction == 3)
            tex_color = get_texture_pixel(game->element->texture->south_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);

        put_pixel(screen_x, start_y, tex_color, game);
        start_y++;
    }

    for (int y = end; y < HEIGHT; y++)
        put_pixel(screen_x, y, game->element->floor_color->converted_color, game);
}



int draw_loop(t_game *game)
{
    t_player *player = &game->player;
    move_player(player, game);
    clear_image(game);

    if (DEBUG)
    {
        draw_square(player->playerX, player->playerY, 10, 0x00FFFF, game);
        draw_map(game);
    }

    float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;

    while (i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

