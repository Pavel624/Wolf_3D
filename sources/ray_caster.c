/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:00:06 by rsatterf          #+#    #+#             */
/*   Updated: 2019/09/12 18:00:49 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ray_step_x(t_wolf_3d *wolf)
{
	if (wolf->ray_dir_x < 0)
	{
		wolf->side_dist_x = (wolf->pos_x - wolf->map_x) * wolf->delta_dist_x;
		return (-1);
	}
	else
	{
		wolf->side_dist_x = (wolf->map_x + 1.0 - wolf->pos_x)
			* wolf->delta_dist_x;
		return (1);
	}
}

int		ray_step_y(t_wolf_3d *wolf)
{
	if (wolf->ray_dir_y < 0)
	{
		wolf->side_dist_y = (wolf->pos_y - wolf->map_y) * wolf->delta_dist_y;
		return (-1);
	}
	else
	{
		wolf->side_dist_y = (wolf->map_y + 1.0 - wolf->pos_y)
			* wolf->delta_dist_y;
		return (1);
	}
}

void	ray_step_init(t_wolf_3d *wolf, int step_x, int step_y)
{
	while (wolf->hit == 0)
	{
		if ((wolf->side_dist_x < wolf->side_dist_y))
		{
			wolf->side_dist_x += wolf->delta_dist_x;
			wolf->map_x += step_x;
			wolf->side = 0;
		}
		else
		{
			wolf->side_dist_y += wolf->delta_dist_y;
			wolf->map_y += step_y;
			wolf->side = 1;
		}
		if (wolf->map[wolf->map_x][wolf->map_y] > 0)
			wolf->hit = 1;
	}
}

void	ray_side_init(t_wolf_3d *wolf, int step_x, int step_y)
{
	if (wolf->side == 0)
		wolf->wall_dist = (wolf->map_x - wolf->pos_x +
			(1 - step_x) * 1.0 / 2) / wolf->ray_dir_x;
	else
		wolf->wall_dist = (wolf->map_y - wolf->pos_y +
			(1 - step_y) * 1.0 / 2) / wolf->ray_dir_y;
}

void	ray_caster(t_wolf_3d *wolf)
{
	int	x;
	int	step_x;
	int	step_y;

	x = 0;
	while (x < WIDTH)
	{
		ray_caster_init(wolf, x);
		wolf->hit = 0;
		step_x = ray_step_x(wolf);
		step_y = ray_step_y(wolf);
		ray_step_init(wolf, step_x, step_y);
		ray_side_init(wolf, step_x, step_y);
		wolf->line_height = (int)(HEIGHT / wolf->wall_dist);
		wolf->draw_start = HEIGHT / 2 - wolf->line_height / 2;
		if (wolf->draw_start < 0)
			wolf->draw_start = 0;
		wolf->draw_end = HEIGHT / 2 + wolf->line_height / 2;
		if (wolf->draw_end >= HEIGHT)
			wolf->draw_end = HEIGHT - 1;
		draw_walls(x, wolf->side, wolf);
		draw_floor(x, wolf->side, wolf);
		x++;
	}
}
