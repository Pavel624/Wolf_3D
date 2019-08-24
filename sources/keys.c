/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:07:28 by nbethany          #+#    #+#             */
/*   Updated: 2019/08/24 17:07:30 by nbethany         ###   ########.fr       */
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
        wolf->pos_x += wolf->dir_x * wolf->move_speed;
        wolf->pos_y += wolf->dir_y * wolf->move_speed;
    }
    else if (key == KEY_DOWN)
    {
        wolf->pos_x -= wolf->dir_x * wolf->move_speed;
        wolf->pos_y -= wolf->dir_y * wolf->move_speed;
    }
    ray_caster(wolf);
    return (1);
}