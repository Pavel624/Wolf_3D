/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:45:02 by nbethany          #+#    #+#             */
/*   Updated: 2019/08/24 13:45:05 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int			index_matr(int row, int column, int map_width)
{
    return (row * map_width + column);
}

void		img_pixel_put(t_image *img, int x, int y, int color)
{
    if (x>= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        *(int *)(img->ptr + (int)(index_matr(y, x, WIDTH) * img->bpp)) = color;
}

void init_wolf(t_wolf_3d *wolf)
{
    wolf->pos_x = 2;
    wolf->pos_y = 2;
    wolf->dir_x = -1;
    wolf->dir_y = 0;
    wolf->plane_x = 0;
    wolf->plane_y = 0.66;
    wolf->move_speed = 0.2;
    wolf->rotate_speed = M_PI / 12;
    wolf->color = 0;
    // FOV = 2 * arctan(planeY / 1.0) - in degrees
}

void draw_walls(int x, int start, int end, t_wolf_3d *wolf)
{
    while (++start <= end)
        img_pixel_put(&wolf->image, x, start, wolf->color);
}

void ray_caster(t_wolf_3d *wolf)
{
    int x;
    int line_height;
    int draw_start;
    //direction of the ray (1 or -1 for both step-x and step_ y)
    int step_x;
    int step_y;
    int side;
    int hit;

    x = 0;
    while (x < WIDTH)
    {
        // camera_x belongs to [-1;1]
        wolf->camera_x = 2 * x / (double) WIDTH - 1;
        wolf->ray_dir_x = wolf->dir_x + wolf->plane_x * wolf->camera_x;
        wolf->ray_dir_y = wolf->dir_y + wolf->plane_y * wolf->camera_x;

        // in which coordinates ray is now
        wolf->map_x = (int) wolf->pos_x;
        wolf->map_y = (int) wolf->pos_y;

        wolf->delta_dist_x = ABS(1.0 / wolf->ray_dir_x);
        wolf->delta_dist_y = ABS(1.0 / wolf->ray_dir_y);

        hit = 0;

        if (wolf->ray_dir_x < 0)
        {
            step_x = -1;
            wolf->side_dist_x = (wolf->pos_x - wolf->map_x) * wolf->delta_dist_x;
        }
        else
        {
            step_x = 1;
            wolf->side_dist_x = (wolf->map_x + 1.0 - wolf->pos_x) * wolf->delta_dist_x;
        }

        if (wolf->ray_dir_y < 0)
        {
            step_y = -1;
            wolf->side_dist_y = (wolf->pos_y - wolf->map_y) * wolf->delta_dist_y;
        }
        else
        {
            step_y = 1;
            wolf->side_dist_y = (wolf->map_y + 1.0 - wolf->pos_y) * wolf->delta_dist_y;
        }
        while (hit == 0)
        {
            if (wolf->side_dist_x < wolf->side_dist_y)
            {
                wolf->side_dist_x += wolf->delta_dist_x;
                wolf->map_x += step_x;
                side = 0;
            }
            else
            {
                wolf->side_dist_y += wolf->delta_dist_y;
                wolf->map_y += step_y;
                side = 1;
            }
            if (wolf->map[wolf->map_x][wolf->map_y] > 0)
                hit = 1;
        }
        if (side == 0)
            wolf->wall_dist = (wolf->map_x - wolf->pos_x + (1 - step_x) * 1.0 / 2) / wolf->ray_dir_x;
        else
            wolf->wall_dist = (wolf->map_y - wolf->pos_y + (1 - step_y) * 1.0 / 2) / wolf->ray_dir_y;

        // height of line to draw on the screen
        line_height = (int) (HEIGHT / wolf->wall_dist);

        wolf->color = 0x87CEEB;
        draw_walls(x, 0, HEIGHT - 1, wolf);
        // highest and lowest pixel to calculate
        draw_start = HEIGHT / 2 - line_height / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end;
        draw_end = HEIGHT / 2 + line_height / 2;
        if (draw_end >= HEIGHT)
            draw_end = HEIGHT - 1;
        if (wolf->map[wolf->map_x][wolf->map_y] == 1)
            wolf->color = 0xFF0000;
        else if (wolf->map[wolf->map_x][wolf->map_y] == 2)
            wolf->color = 0x00FF00;
        else if (wolf->map[wolf->map_x][wolf->map_y] == 3)
            wolf->color = 0x0000FF;
        else
            wolf->color = 0xFFFFFF;
        if (side == 0)
            wolf->color /= 2;
        draw_walls(x, draw_start, draw_end, wolf);
        x++;
    }
    mlx_put_image_to_window(wolf->mlx, wolf->window, wolf->image.image, 0, 0);
}
