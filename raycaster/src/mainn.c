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
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

// touch function 
bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
    int y = py / BLOCK;
    if(game->map[y][x] == '1')
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


// raycasting functions
// SO CLOSE for the 4 walls
void draw_line(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->playerX;
    float ray_y = player->playerY;

    int texture_direction = 0;  // 0 = east, 1 = west, 2 = north, 3 = south
    int hit_vertical = 0;       // 1 = vertical hit, 0 = horizontal hit

    // Raycasting loop to find wall hit
    while (!touch(ray_x, ray_y, game))
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
    }

    // Determine which wall side the ray intersects and adjust texture
    if (fabs(cos_angle) > fabs(sin_angle))  // Vertical hit (East/West walls)
    {
        if (cos_angle > 0)
            texture_direction = 0;  // East wall
        else
            texture_direction = 1;  // West wall
        hit_vertical = 1;
    }
    else  // Horizontal hit (North/South walls)
    {
        if (sin_angle > 0)
            texture_direction = 3;  // South wall
        else
            texture_direction = 2;  // North wall
        hit_vertical = 0;
    }

    if (!DEBUG)
    {
        // Calculate distance to the wall and adjust the height of the wall slice
        float dist = fixed_dist(player->playerX, player->playerY, ray_x, ray_y, game);
        float height = (BLOCK / dist) * (WIDTH / 2);
        int start_y = (HEIGHT - height) / 2;
        int end = start_y + height;

        // Draw ceiling
        for (int y = 0; y < start_y; y++)
            put_pixel(i, y, game->element->ceiling_color->converted_color, game);

        // Draw wall with texture based on the direction of the wall
        while (start_y < end)
        {
            // Calculate texture Y coordinate for the wall slice
            int tex_y = (start_y - (HEIGHT - height) / 2) * game->element->texture->height / height;

            int tex_x = 0;
            if (hit_vertical)
                tex_x = (int)(ray_y) % BLOCK;  // Horizontal texture for East/West walls
            else
                tex_x = (int)(ray_x) % BLOCK;  // Vertical texture for North/South walls

            // Fetch texture color for the given coordinates
            int tex_color = 0;
            if (texture_direction == 0)  // East texture
            {
                tex_color = get_texture_pixel(game->element->texture->east_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
            }
            else if (texture_direction == 1)  // West texture
            {
                tex_color = get_texture_pixel(game->element->texture->west_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
            }
            else if (texture_direction == 2)  // North texture
            {
                // printf("North texture being applied\n"); // Debugging
                tex_color = get_texture_pixel(game->element->texture->north_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
            }
            else if (texture_direction == 3)  // South texture
            {
                // printf("South texture being applied\n"); // Debugging
                tex_color = get_texture_pixel(game->element->texture->south_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
            }

            put_pixel(i, start_y, tex_color, game);
            start_y++;
        }

        // Draw floor
        for (int y = end; y < HEIGHT; y++)
            put_pixel(i, y, game->element->floor_color->converted_color, game);
    }
}

//This does just east and west walls but well
// void draw_line(t_player *player, t_game *game, float start_x, int i)
// {
//     float cos_angle = cos(start_x);
//     float sin_angle = sin(start_x);
//     float ray_x = player->playerX;
//     float ray_y = player->playerY;

//     int texture_direction = 0; // 0 = east, 1 = west, 2 = north, 3 = south
//     int hit_vertical = 0; // 1 = vertical hit, 0 = horizontal hit

//     // Raycasting loop to find wall hit
//     while (!touch(ray_x, ray_y, game))
//     {
//         ray_x += cos_angle;
//         ray_y += sin_angle;
//     }

//     // Determine which wall side the ray intersects and adjust texture
//     if (cos_angle > 0) 
//     {
//         texture_direction = 0;  // Ray hits east wall
//         hit_vertical = 1;  // Vertical hit for East/West
//     }
//     else if (cos_angle < 0) 
//     {
//         texture_direction = 1;  // Ray hits west wall
//         hit_vertical = 1;  // Vertical hit for East/West
//     }
//     else if (sin_angle > 0) 
//     {
//         texture_direction = 3;  // Ray hits south wall
//         hit_vertical = 0;  // Horizontal hit for North/South
//     }
//     else if (sin_angle < 0) 
//     {
//         texture_direction = 2;  // Ray hits north wall
//         hit_vertical = 0;  // Horizontal hit for North/South
//     }

//     if (!DEBUG)
//     {
//         // Calculate distance to the wall and adjust the height of the wall slice
//         float dist = fixed_dist(player->playerX, player->playerY, ray_x, ray_y, game);
//         float height = (BLOCK / dist) * (WIDTH / 2);
//         int start_y = (HEIGHT - height) / 2;
//         int end = start_y + height;

//         // Draw ceiling
//         for (int y = 0; y < start_y; y++)
//             put_pixel(i, y, game->element->ceiling_color->converted_color, game);

//         // Draw wall with texture based on the direction of the wall
//         while (start_y < end)
//         {
//             // Calculate texture Y coordinate for the wall slice
//             int tex_y = (start_y - (HEIGHT - height) / 2) * game->element->texture->height / height;

//             int tex_x = 0;
//             if (hit_vertical) 
//                 tex_x = (int)(ray_y) % BLOCK; // Horizontal texture for East/West walls
//             else 
//                 tex_x = (int)(ray_x) % BLOCK; // Vertical texture for North/South walls

//             // Fetch texture color for the given coordinates
//             int tex_color = 0;
//             if (texture_direction == 0)  // East texture
//                 tex_color = get_texture_pixel(game->element->texture->east_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
//             else if (texture_direction == 1)  // West texture
//                 tex_color = get_texture_pixel(game->element->texture->west_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
//             else if (texture_direction == 2)  // North texture
//                 tex_color = get_texture_pixel(game->element->texture->north_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);
//             else if (texture_direction == 3)  // South texture
//                 tex_color = get_texture_pixel(game->element->texture->south_data, tex_x, tex_y, game->element->texture->size_line, game->element->texture->bpp);

//             put_pixel(i, start_y, tex_color, game);
//             start_y++;
//         }

//         // Draw floor
//         for (int y = end; y < HEIGHT; y++)
//             put_pixel(i, y, game->element->floor_color->converted_color, game);
//     }
// }

// void draw_line(t_player *player, t_game *game, float start_x, int i)
// {
//     float cos_angle = cos(start_x);
//     float sin_angle = sin(start_x);
//     float ray_x = player->playerX;
//     float ray_y = player->playerY;

//     while(!touch(ray_x, ray_y, game))
//     {
//         if(DEBUG)
//             put_pixel(ray_x, ray_y, 0xFF0000, game);
//         ray_x += cos_angle;
//         ray_y += sin_angle;
//     }
//     if(!DEBUG)
//     {
//         float dist = fixed_dist(player->playerX, player->playerY, ray_x, ray_y, game);
//         float height = (BLOCK / dist) * (WIDTH / 2);
//         int start_y = (HEIGHT - height) / 2;
//         int end = start_y + height;
// 		for (int y = 0; y < start_y; y++)
//         	put_pixel(i, y, game->element->ceiling_color->converted_color, game); 

//         //this drawas the wall
//         while(start_y < end)
//         {
//             put_pixel(i, start_y, 0xFFF00, game);
//             start_y++;
//         }

//         //this draws the floor
// 		for (int y = end; y < HEIGHT; y++)
//         	put_pixel(i, y, game->element->floor_color->converted_color, game); // i used this to draw the floor
//     }
// }

int draw_loop(t_game *game)
{
    t_player *player = &game->player;
    move_player(player);
    clear_image(game);
    if(DEBUG)
    {
        draw_square(player->playerX, player->playerY, 10, 0x00FFFF, game);
        draw_map(game);
    }
    float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;
    while(i < WIDTH)
    {
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}

// int main(int ac, char **argv)
// {
//     t_game game;
//     // init

//     // Assuming valid_extension_args_no and parsing_func are defined elsewhere
//     // if (!valid_extension_file_check(argv[1], ac, "cub"))
//     //     return (0);
    // init_game(&game, argv[1]);
    
	
//     // hooks
//     mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
//     mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
//     // draw loop
    // mlx_loop_hook(game.mlx, draw_loop, &game);

//     mlx_loop(game.mlx);
//     return 0;
// }
