/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 13:45:02 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/12 18:00:57 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	img_pixel_put_one(t_image *img, int x, int y, int color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		*(int *)(img->ptr + (int)((WIDTH * y + x) * img->bpp)) = color;
}

void	color(t_wolf_3d *wolf)
{
	int	r;
	int	g;
	int	b;

	r = (wolf->tex[wolf->tex_num].ptr[wolf->tex[wolf->tex_num].line_s *
		wolf->tex_y + wolf->tex_x * 4 + 2]) << 16;
	g = (wolf->tex[wolf->tex_num].ptr[wolf->tex[wolf->tex_num].line_s *
		wolf->tex_y + wolf->tex_x * 4 + 1]) << 8;
	b = (wolf->tex[wolf->tex_num].ptr[wolf->tex[wolf->tex_num].line_s *
		wolf->tex_y + wolf->tex_x * 4]);
	wolf->color = r + g + b;
	wolf->color = wolf->color >> 1 & 0x7F7F7F;
}

void	init_wolf(t_wolf_3d *wolf)
{
	wolf->dir_x = -1;
	wolf->dir_y = 0;
	wolf->plane_x = 0;
	wolf->plane_y = 0.66;
	wolf->move_speed = 0.059;
	wolf->rotate_speed = M_PI / 72;
	wolf->color = 0;
	wolf->flag = 0;
	wolf->shot_flag = 0;
	wolf->shot_frames = 16;
	wolf->move.forward = 0;
	wolf->move.back = 0;
	wolf->move.left = 0;
	wolf->move.right = 0;
	load_textures(wolf);
	load_textures2(wolf);
}

int		loop(t_wolf_3d *wolf)
{
	movement(wolf);
	draw_sky(&wolf->image, wolf);
	ray_caster(wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->window, wolf->image.image, 0, 0);
	animate_pistol(wolf);
	return (0);
}

void	ray_caster_init(t_wolf_3d *wolf, int x)
{
	wolf->camera_x = 2 * x / (double)WIDTH - 1;
	wolf->ray_dir_x = wolf->dir_x + wolf->plane_x * wolf->camera_x;
	wolf->ray_dir_y = wolf->dir_y + wolf->plane_y * wolf->camera_x;
	wolf->map_x = (int)wolf->pos_x;
	wolf->map_y = (int)wolf->pos_y;
	wolf->delta_dist_x = fabs(1.0 / wolf->ray_dir_x);
	wolf->delta_dist_y = fabs(1.0 / wolf->ray_dir_y);
}
