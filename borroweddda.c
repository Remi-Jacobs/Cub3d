#include "../includes/game.h"


void	init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	init_texture_pixels(t_game *data)
{
	int	i;

	if (data->tex_pixels)
		free_array_2d((void **)data->tex_pixels);
	data->tex_pixels = ft_calloc(data->win_height + 1,
			sizeof * data->tex_pixels);
	if (!data->tex_pixels)
		clean_exit(data, -42);
	i = 0;
	while (i < data->win_height)
	{
		data->tex_pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->tex_pixels);
		if (!data->tex_pixels[i])
			clean_exit(data, -42);
		i++;
	}
}

static void	calculate_line_height(t_ray *ray, t_game *data)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = data->element->map_array->player_column + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = data->element->map_array->player_row + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

static void	perform_dda(t_game *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25 || ray->map_x < 0.25
			|| ray->map_y > data->element->map_array->max_map_column - 0.25
			|| ray->map_x > data->element->map_array->max_map_row - 1.25)
			break ;
		else if (data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static void	set_dda(t_ray *ray, t_game *data)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data->element->map_array->player_row - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x
			= (ray->map_x + 1.0 - data->element->map_array->player_row) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->element->map_array->player_column - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y
			= (ray->map_y + 1.0 - data->element->map_array->player_column) * ray->deltadist_y;
	}
}

static void	init_raycasting_info(int x, t_ray *ray, t_game *data)
{
	init_ray(ray);
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = data->player.player_dirX + data->player.player_planeX * ray->camera_x;
	ray->dir_y = data->player.player_dirY + data->player.player_planeY * ray->camera_x;
	ray->map_x = data->element->map_array->player_row;
	ray->map_y = data->element->map_array->player_column;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);

}

int	raycasting(t_game *data)
{
	t_ray	*ray;
	int		x;

	x = 0;
	ray = &data->ray;
	while (x < WIDTH)
	{
		init_raycasting_info(x, ray, data);
		set_dda(ray, data);
		perform_dda(data, ray);
		calculate_line_height(ray, data);
		update_texture_pixels(data, ray, x);
		x++;
	}
	return (0);
}