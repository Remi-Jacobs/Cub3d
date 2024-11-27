/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 01:44:02 by danevans          #+#    #+#             */
/*   Updated: 2024/11/25 21:14:27 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../mlx/mlx.h"

// #define TILE_SIZE 32
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 150

void	ft_error_exit(t_parser *data, char *str)
{
	free_parser_struct(data);
	printf("%s\n", str);
}

// void draw_minimap(t_parser *data)
// {
//     int x, y;
//     int tile_color;

//     for (y = 0; y < data->column; y++)
//     {
//         for (x = 0; x < data->row; x++)
//         {
//             // Color the tiles differently depending on the value of the map
//             if (data->map[y][x] == 1)
//                 tile_color = 0xFF0000;  // Red for walls
//             else
//                 tile_color = 0x00FF00;  // Green for empty spaces

//             // Draw the tile in the minimap area (scaled by TILE_SIZE)
//             mlx_pixel_put(data->mlx_ptr, data->win_ptr, 
//                 WIN_WIDTH - MINIMAP_WIDTH + x * TILE_SIZE,  // X position in minimap area
//                 WIN_HEIGHT - MINIMAP_HEIGHT + y * TILE_SIZE,  // Y position in minimap area
//                 tile_color);
//         }
//     }
// }

// Function to create an image filled with a color
void *create_color_image(t_parser *data, int color)
{
    int *pixels;
    void *img;
    int width = TILE_SIZE;
    int height = TILE_SIZE;
    int bpp, size_line, endian;

    // Create the image with the specified width and height
    img = mlx_new_image(data->mlx_ptr, width, height);
    if (!img)
        return NULL;

    // Get the pixel data address along with some extra info (bits per pixel, size line, and endian)
    pixels = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
    if (!pixels)
        return NULL;

    // Set the color for every pixel in the image
    for (int i = 0; i < width * height; i++)
        pixels[i] = color;

    return img;
}


void ft_render_screen(t_parser *data)
{
    int x, y;
    void *tile_img;

    y = -1;
    while (++y < data->row)
    {
        x = -1;
        while (++x < data->column)
        {
            // Create an image filled with color (0x00FFFF)
            tile_img = create_color_image(data, 0xFFFF00);
            if (tile_img)
            {
                // Put the image onto the window
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, tile_img, x * TILE_SIZE, y * TILE_SIZE);
                // Free the image after it has been drawn
                mlx_destroy_image(data->mlx_ptr, tile_img);
            }
        }
    }
}

void ft_render_screen2(t_parser *data)
{
    int x, y;
    void *tile_img;
	int minimap_x_offset = 500; // Starting x-coordinate for the minimap
    int minimap_y_offset = 375;

    y = -1;
    while (++y < data->row)
    {
        x = -1;
        while (++x < data->column)
        {
            // Create an image filled with color (0x00FFFF)
            tile_img = create_color_image(data, 0xFF0000);
            if (tile_img)
            {
				int minimap_x = (x - minimap_x_offset / 13) * 13;
                    int minimap_y = (y - minimap_y_offset / 13) * 13;
                // Put the image onto the window
                // mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, tile_img, x * 13, y * 13);
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, tile_img, minimap_x_offset + minimap_x, minimap_y_offset + minimap_y);

                // Free the image after it has been drawn
                mlx_destroy_image(data->mlx_ptr, tile_img);
            }
        }
    }
}

int main(int ac, char **argv)
{
    t_parser *data;

    // Assuming valid_extension_args_no and parsing_func are defined elsewhere
    if (!valid_extension_args_no(argv[1], ac, "cub"))
        return (0);
    data = parsing_func(argv[1]);
    if (data == NULL)
        return (0);

    // Initialize mlx and create the window
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        return (1);
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->column * TILE_SIZE, data->row * TILE_SIZE, "cub3D");
    if (!data->win_ptr)
        return (1);

    // // Render the screen with colored tiles using images
    ft_render_screen(data);
    ft_render_screen2(data);

    // Enter the mlx loop to display the window
    mlx_loop(data->mlx_ptr);

    return (0);
}

