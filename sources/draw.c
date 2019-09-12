/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:51:11 by rsatterf          #+#    #+#             */
/*   Updated: 2019/09/12 17:52:23 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_floor2(t_wolf_3d *wolf, double floor_x_wall,
	double floor_y_wall, int x)
{
	double	current_dist;
	double	weight;
	double	current_floor_x;
	double	current_floor_y;
	int		y;

	y = wolf->draw_end + 1;
	while (y < HEIGHT)
	{
		current_dist = HEIGHT / (2.0 * y - HEIGHT);
		weight = current_dist / wolf->wall_dist;
		current_floor_x = weight * floor_x_wall + (1.0 - weight) * wolf->pos_x;
		current_floor_y = weight * floor_y_wall + (1.0 - weight) * wolf->pos_y;
		wolf->tex_x = (int)(current_floor_x * TEX_WIDTH) % TEX_WIDTH;
		wolf->tex_y = (int)(current_floor_y * TEX_HEIGHT) % TEX_HEIGHT;
		if (wolf->map[(int)current_floor_x][(int)current_floor_y] == 0)
			wolf->tex_num = 0;
		else
			wolf->tex_num = abs(wolf->map[(int)current_floor_x]
				[(int)current_floor_y] + 1) % 4;
		color(wolf);
		img_pixel_put_one(&wolf->image, x, y, wolf->color);
		y++;
	}
}

void	draw_floor3(t_wolf_3d *wolf)
{
	if (wolf->draw_end < 0)
		wolf->draw_end = HEIGHT;
}

void	draw_floor(int x, int side, t_wolf_3d *wolf)
{
	double	floor_x_wall;
	double	floor_y_wall;

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
	draw_floor3(wolf);
	draw_floor2(wolf, floor_x_wall, floor_y_wall, x);
}

void	draw_walls(int x, int side, t_wolf_3d *wolf)
{
	int	d;

	wolf->tex_num = (wolf->map[wolf->map_x][wolf->map_y] - 1) % 4;
	if (side == 0)
		wolf->wall_x = wolf->pos_y + wolf->wall_dist * wolf->ray_dir_y;
	else
		wolf->wall_x = wolf->pos_x + wolf->wall_dist * wolf->ray_dir_x;
	wolf->wall_x -= floor(wolf->wall_x);
	wolf->tex_x = (int)(wolf->wall_x * (double)TEX_WIDTH);
	if ((side == 0 && wolf->ray_dir_x > 0) ||
		(side == 1 && wolf->ray_dir_y < 0))
		wolf->tex_x = TEX_WIDTH - wolf->tex_x - 1;
	while (wolf->draw_start < wolf->draw_end)
	{
		d = wolf->draw_start - HEIGHT * 0.5f + wolf->line_height * 0.5f;
		wolf->tex_y = ((d * TEX_HEIGHT) / wolf->line_height);
		ft_memcpy(&wolf->color, &wolf->tex[wolf->tex_num].ptr[wolf->tex_y % 64 *
			wolf->tex[wolf->tex_num].line_s + wolf->tex_x % 64 *
				wolf->tex[wolf->tex_num].bpp], sizeof(int));
		if (side == 1)
			wolf->color = wolf->color >> 1 & 0x7F7F7F;
		img_pixel_put_one(&wolf->image, x, wolf->draw_start, wolf->color);
		wolf->draw_start++;
	}
}

void	draw_sky(t_image *img, t_wolf_3d *wolf)
{
	wolf->tex_x = 0;
	while (wolf->tex_x < WIDTH)
	{
		wolf->tex_y = 0;
		while (wolf->tex_y < HEIGHT / 2)
		{
			ft_memcpy(img->ptr + 4 * WIDTH * wolf->tex_y + wolf->tex_x * 4,
				&wolf->tex[4].ptr[wolf->tex_y % 512 * wolf->tex[4].line_s +
					wolf->tex_x % 512 * wolf->tex[4].bpp], sizeof(int));
			wolf->tex_y++;
		}
		wolf->tex_x++;
	}
}
