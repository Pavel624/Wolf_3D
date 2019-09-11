/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 01:47:20 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/11 21:48:55 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	forward(t_wolf_3d *wolf)
{
	static int i = 0;

	if (i % 40 == 0)
		OS_VER == 0 ? system("afplay -v 0.5 audio/shag0.wav &") :
		system("paplay --volume 32768 audio/shag0.wav");
	if (i == 1000)
		i = 0;
	i++;
	if (wolf->map[(int)(wolf->pos_x + wolf->dir_x *
									wolf->move_speed)][(int)wolf->pos_y] < 1)
		wolf->pos_x += wolf->dir_x * wolf->move_speed;
	if (wolf->map[(int)wolf->pos_x][(int)(wolf->pos_y + wolf->dir_y *
									wolf->move_speed)] < 1)
		wolf->pos_y += wolf->dir_y * wolf->move_speed;
}

void	back(t_wolf_3d *wolf)
{
	static	int	i = 0;

	if (i % 40 == 0)
		OS_VER == 0 ? system("afplay -v 0.5 audio/shag0.wav &") :
		system("paplay --volume 32768 audio/shag0.wav");
	if (i == 1000)
		i = 0;
	i++;
	if (wolf->map[(int)(wolf->pos_x - wolf->dir_x *
							wolf->move_speed)][(int)wolf->pos_y] < 1)
		wolf->pos_x -= wolf->dir_x * wolf->move_speed;
	if (wolf->map[(int)wolf->pos_x][(int)(wolf->pos_y -
							wolf->dir_y * wolf->move_speed)] < 1)
		wolf->pos_y -= wolf->dir_y * wolf->move_speed;
}

void	left(t_wolf_3d *wolf)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = wolf->dir_x;
	wolf->dir_x = wolf->dir_x * cos(wolf->rotate_speed) -
						wolf->dir_y * sin(wolf->rotate_speed);
	wolf->dir_y = old_dir_x * sin(wolf->rotate_speed) +
						wolf->dir_y * cos(wolf->rotate_speed);
	old_plane_x = wolf->plane_x;
	wolf->plane_x = wolf->plane_x * cos(wolf->rotate_speed) -
						wolf->plane_y * sin(wolf->rotate_speed);
	wolf->plane_y = old_plane_x * sin(wolf->rotate_speed) +
						wolf->plane_y * cos(wolf->rotate_speed);
}

void	right(t_wolf_3d *wolf)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = wolf->dir_x;
	wolf->dir_x = wolf->dir_x * cos(-wolf->rotate_speed) -
						wolf->dir_y * sin(-wolf->rotate_speed);
	wolf->dir_y = old_dir_x * sin(-wolf->rotate_speed) +
						wolf->dir_y * cos(-wolf->rotate_speed);
	old_plane_x = wolf->plane_x;
	wolf->plane_x = wolf->plane_x * cos(-wolf->rotate_speed) -
						wolf->plane_y * sin(-wolf->rotate_speed);
	wolf->plane_y = old_plane_x * sin(-wolf->rotate_speed) +
						wolf->plane_y * cos(-wolf->rotate_speed);
}

void	movement(t_wolf_3d *wolf)
{
	if (wolf->move.forward == 1)
		forward(wolf);
	if (wolf->move.back == 1)
		back(wolf);
	if (wolf->move.right == 1)
		right(wolf);
	if (wolf->move.left == 1)
		left(wolf);
}
