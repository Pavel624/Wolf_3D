/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:07:28 by nbethany          #+#    #+#             */
/*   Updated: 2019/08/30 13:42:51 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		key_down(int key)
{
    if (key == KEY_ESC)
        exit(EXIT_SUCCESS);
    return (1);
}

int		key_trans(int key, t_wolf_3d *wolf)
{
    if (key == KEY_UP)
    {
            if (wolf->map[(int) (wolf->pos_x + wolf->dir_x * wolf->move_speed)][(int) wolf->pos_y] == 0)
                wolf->pos_x += wolf->dir_x * wolf->move_speed;
            if (wolf->map[(int) wolf->pos_x][(int) (wolf->pos_y + wolf->dir_y * wolf->move_speed)] == 0)
                wolf->pos_y += wolf->dir_y * wolf->move_speed;
			
    }
    else if (key == KEY_DOWN)
    {
        //if ((int)(wolf->pos_x - wolf->dir_x * wolf->move_speed) < wolf->lines)
        //{
            if (wolf->map[(int) (wolf->pos_x - wolf->dir_x * wolf->move_speed)][(int) wolf->pos_y] == 0)
                wolf->pos_x -= wolf->dir_x * wolf->move_speed;
            if (wolf->map[(int) wolf->pos_x][(int) (wolf->pos_y - wolf->dir_y * wolf->move_speed)] == 0)
                wolf->pos_y -= wolf->dir_y * wolf->move_speed;
		//}
		
    }

    else if (key == KEY_LEFT)
    {
        double oldDirX = wolf->dir_x;
        wolf->dir_x = wolf->dir_x * cos(wolf->rotate_speed) - wolf->dir_y * sin(wolf->rotate_speed);
        wolf->dir_y = oldDirX * sin(wolf->rotate_speed) + wolf->dir_y * cos(wolf->rotate_speed);
        double oldPlaneX = wolf->plane_x;
        wolf->plane_x = wolf->plane_x * cos(wolf->rotate_speed) - wolf->plane_y * sin(wolf->rotate_speed);
        wolf->plane_y = oldPlaneX * sin(wolf->rotate_speed) + wolf->plane_y * cos(wolf->rotate_speed);
    }
    else if (key == KEY_RIGHT)
    {
        double oldDirX = wolf->dir_x;
        wolf->dir_x = wolf->dir_x * cos(-wolf->rotate_speed) - wolf->dir_y * sin(-wolf->rotate_speed);
        wolf->dir_y = oldDirX * sin(-wolf->rotate_speed) + wolf->dir_y * cos(-wolf->rotate_speed);
        double oldPlaneX = wolf->plane_x;
        wolf->plane_x = wolf->plane_x * cos(-wolf->rotate_speed) - wolf->plane_y * sin(-wolf->rotate_speed);
        wolf->plane_y = oldPlaneX * sin(-wolf->rotate_speed) + wolf->plane_y * cos(-wolf->rotate_speed);
    }
		wolf->flag = 0;
        ray_caster(wolf);
    return (1);
}