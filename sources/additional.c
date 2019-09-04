/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:45:02 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/04 18:46:09 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void        load_textures(t_wolf_3d *wolf)
{
    int tex_width = 64;
    int tex_height = 64;
    int a = 512;
    int b = 512;
    int pistol_res_width = 228;
    int pistol_res_height = 317;

    wolf->tex[0].image = mlx_xpm_file_to_image(wolf->mlx,"textures/stone.xpm", &tex_width, &tex_height);
    wolf->tex[0].ptr = mlx_get_data_addr(wolf->tex[0].image, &wolf->tex[0].bpp, &wolf->tex[0].line_s, &wolf->tex[0].endian);
    wolf->tex[0].bpp /= 8;
    wolf->tex[1].image = mlx_xpm_file_to_image(wolf->mlx,"textures/sand.xpm", &tex_width, &tex_height);
    wolf->tex[1].ptr = mlx_get_data_addr(wolf->tex[1].image, &wolf->tex[1].bpp, &wolf->tex[1].line_s, &wolf->tex[1].endian);
    wolf->tex[1].bpp /= 8;
    wolf->tex[2].image = mlx_xpm_file_to_image(wolf->mlx,"textures/wood.xpm", &tex_width, &tex_height);
    wolf->tex[2].ptr = mlx_get_data_addr(wolf->tex[2].image, &wolf->tex[2].bpp, &wolf->tex[2].line_s, &wolf->tex[2].endian);
    wolf->tex[2].bpp /= 8;
    wolf->tex[3].image = mlx_xpm_file_to_image(wolf->mlx,"textures/mossy.xpm", &tex_width, &tex_height);
    wolf->tex[3].ptr = mlx_get_data_addr(wolf->tex[3].image, &wolf->tex[3].bpp, &wolf->tex[3].line_s, &wolf->tex[3].endian);
    wolf->tex[3].bpp /= 8;
    wolf->tex[4].image = mlx_xpm_file_to_image(wolf->mlx,"textures/sky.xpm", &a, &b);
    wolf->tex[4].ptr = mlx_get_data_addr(wolf->tex[4].image, &wolf->tex[4].bpp, &wolf->tex[4].line_s, &wolf->tex[4].endian);
    wolf->tex[4].bpp /= 8;
    wolf->pistol[0].image = mlx_xpm_file_to_image(wolf->mlx,"textures/gun_1.xpm", &pistol_res_width, &pistol_res_height);
    wolf->pistol[1].image = mlx_xpm_file_to_image(wolf->mlx,"textures/gun_2.xpm", &pistol_res_width, &pistol_res_height);
    wolf->pistol[2].image = mlx_xpm_file_to_image(wolf->mlx,"textures/gun_3.xpm", &pistol_res_width, &pistol_res_height);
    wolf->pistol[3].image = mlx_xpm_file_to_image(wolf->mlx,"textures/gun_4.xpm", &pistol_res_width, &pistol_res_height);
}

int			index_matr(int row, int column, int map_width)
{
    return (row * map_width + column);
}

void		img_pixel_put_one(t_image *img, int x, int y, int color)
{
    if (x>= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        *(int *) (img->ptr + (int) (index_matr(y, x, WIDTH) * img->bpp)) = color;
}

void		img_pixel_put_two(t_image *img, int x, int y, t_wolf_3d *wolf)
{
    if (x>= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        //*(int *) (img->ptr + (int) (index_matr(y, x, WIDTH) * img->bpp)) = color;
        ft_memcpy(img->ptr + 4 * WIDTH * y + x * 4, &wolf->tex[wolf->tex_num].ptr[wolf->tex_y % 64 * wolf->tex[wolf->tex_num].line_s + wolf->tex_x % 64 * wolf->tex[wolf->tex_num].bpp], sizeof(int));
}

void	draw_sky(t_image *img,t_wolf_3d *wolf)
{
    wolf->tex_x = 0;
    while (wolf->tex_x < WIDTH)
    {
        wolf->tex_y = 0;
        while (wolf->tex_y < HEIGHT / 2)
        {
            ft_memcpy(img->ptr + 4 * WIDTH * wolf->tex_y + wolf->tex_x * 4, &wolf->tex[4].ptr[wolf->tex_y % 512 * wolf->tex[4].line_s + wolf->tex_x % 512 * wolf->tex[4].bpp], sizeof(int));
            wolf->tex_y++;
        }
        wolf->tex_x++;
    }
}

void pistol_animation(t_wolf_3d *wolf)
{
    if (wolf->shot_frames >= 9)
        mlx_put_image_to_window(wolf->mlx, wolf->window, wolf->pistol[1].image, (WIDTH - 100) / 2, HEIGHT - 300);
    else if (wolf->shot_frames >= 6 && wolf->shot_frames < 9)
        mlx_put_image_to_window(wolf->mlx, wolf->window, wolf->pistol[2].image, (WIDTH - 100) / 2, HEIGHT - 300);
    else if (wolf->shot_frames >= 3 && wolf->shot_frames < 6)
        mlx_put_image_to_window(wolf->mlx, wolf->window, wolf->pistol[3].image, (WIDTH - 100) / 2, HEIGHT - 300);
    else if (wolf->shot_frames == 2)
        mlx_put_image_to_window(wolf->mlx, wolf->window, wolf->pistol[3].image, (WIDTH - 100) / 2, HEIGHT - 300);
    wolf->shot_frames--;
    if (wolf->shot_frames == 1)
    {
        wolf->shot_frames = 12;
        wolf->shot_flag = 0;
    }
}

void	animate_pistol(t_wolf_3d *wolf)
{
    if (wolf->shot_flag == 0)
        mlx_put_image_to_window(wolf->mlx, wolf->window, wolf->pistol[0].image, (WIDTH - 100) / 2, HEIGHT - 300);
    else if (wolf->shot_flag == 1)
        {
        if (wolf->shot_frames == 12)
            system("afplay -v 0.65 audio/gun_shot.wav &");
        pistol_animation(wolf);
    }
}

void draw_floor(int x, int side, t_wolf_3d *wolf)
{
    double floor_x_wall;
    double floor_y_wall;
    double current_dist;
    int y;

    if (side == 0 && wolf->ray_dir_x > 0)
    {
        floor_x_wall = wolf->map_x;
        floor_y_wall = wolf->map_y + wolf->wall_x;
    }
    else if (side == 0 && wolf->ray_dir_x < 0)
    {
        floor_x_wall = wolf->map_x + 1.0;
        floor_y_wall = wolf->map_y + wolf->wall_x;
    }
    else if (side == 1 && wolf->ray_dir_y > 0)
    {
        floor_x_wall = wolf->map_x + wolf->wall_x;
        floor_y_wall = wolf->map_y;
    }
    else
    {
        floor_x_wall = wolf->map_x + wolf->wall_x;
        floor_y_wall = wolf->map_y + 1.0;
    }
    if (wolf->draw_end < 0)
        wolf->draw_end = HEIGHT;

    //wolf->tex_num = wolf->map[wolf->map_x][wolf->map_y] - 1;
    y = wolf->draw_end;
    while (y < HEIGHT)
    {
        current_dist = HEIGHT / (2.0 * y - HEIGHT);
        double weight = current_dist/ wolf->wall_dist;
        double current_floor_x = weight * floor_x_wall + (1.0 - weight) * wolf->pos_x;
        double current_floor_y = weight * floor_y_wall + (1.0 - weight) * wolf->pos_y;

        int floor_tex_x, floor_tex_y;
        floor_tex_x = (int)(current_floor_x * TEX_WIDTH) % TEX_WIDTH;
        floor_tex_y = (int)(current_floor_y * TEX_HEIGHT) % TEX_HEIGHT;
        //need some adjustments to make this piece of code more understandable
        int r = (wolf->tex[1].ptr[wolf->tex[1].line_s * floor_tex_y + floor_tex_x * 4 + 2]) * 65536;
        int g = (wolf->tex[1].ptr[wolf->tex[1].line_s * floor_tex_y + floor_tex_x * 4 + 1]) * 256;
        int b = (wolf->tex[1].ptr[wolf->tex[1].line_s * floor_tex_y + floor_tex_x * 4]);
        wolf->color = r + g + b;
        wolf->color = wolf->color >> 1 & 0x7F7F7F;
        img_pixel_put_one(&wolf->image, x, y, wolf->color);
        y++;
    }

}

void init_wolf(t_wolf_3d *wolf)
{
    wolf->dir_x = -1;
    wolf->dir_y = 0;
    wolf->plane_x = 0;
    wolf->plane_y = 0.66;
    wolf->move_speed = 0.15;
    wolf->rotate_speed = 2 * M_PI / 36;
    wolf->color = 0;
    wolf->flag = 0;
    wolf->shot_flag = 0;
    wolf->shot_frames = 12;
    load_textures(wolf);
    // FOV = 2 * arctan(planeY / 1.0) - in degrees
}

void draw_walls(int x, int side, t_wolf_3d *wolf)
{
    if (wolf->flag == 0)
    {
        draw_sky(&wolf->image, wolf);
        wolf->flag = 1;
    }
    //if (wolf->map[wolf->map_x][wolf->map_y] > 0)
    wolf->tex_num = (wolf->map[wolf->map_x][wolf->map_y] - 1) % 4;
    if (side == 0)
        wolf->wall_x = wolf->pos_y + wolf->wall_dist * wolf->ray_dir_y;
    else
        wolf->wall_x = wolf->pos_x + wolf->wall_dist * wolf->ray_dir_x;
    wolf->wall_x -= floor(wolf->wall_x);
    wolf->tex_x = (int) (wolf->wall_x * (double) TEX_WIDTH);
    if ((side == 0 && wolf->ray_dir_x > 0) || (side == 1 && wolf->ray_dir_y < 0))
        wolf->tex_x = TEX_WIDTH - wolf->tex_x - 1;
    wolf->tex_x = abs(wolf->tex_x);
    while (++wolf->draw_start < wolf->draw_end)
    {
        int d = wolf->draw_start * 256 - HEIGHT * 128 + wolf->line_height * 128;
        wolf->tex_y = abs(((d * TEX_HEIGHT) / wolf->line_height) / 256);
        img_pixel_put_two(&wolf->image, x, wolf->draw_start, wolf);
    }
}

void      loop(t_wolf_3d *wolf)
{
    ray_caster(wolf);
    //animate_pistol(wolf);


}

void ray_caster(t_wolf_3d *wolf)
{
    int x;
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

        wolf->delta_dist_x = fabs(1.0 / wolf->ray_dir_x);
        wolf->delta_dist_y = fabs(1.0 / wolf->ray_dir_y);

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

            if ((wolf->side_dist_x < wolf->side_dist_y))
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
        wolf->line_height = (int) (HEIGHT / wolf->wall_dist);
        // highest and lowest pixel to calculate
        wolf->draw_start = HEIGHT / 2 - wolf->line_height / 2;
        if (wolf->draw_start < 0)
            wolf->draw_start = 0;
        wolf->draw_end = HEIGHT / 2 + wolf->line_height / 2;
        if (wolf->draw_end >= HEIGHT)
            wolf->draw_end = HEIGHT - 1;
        draw_walls(x, side, wolf);
        draw_floor(x, side, wolf);
        x++;
    }
    mlx_put_image_to_window(wolf->mlx, wolf->window, wolf->image.image, 0, 0);
    animate_pistol(wolf);
}
