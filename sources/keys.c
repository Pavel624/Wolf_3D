/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 17:07:28 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/04 18:41:17 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		key_release(int key, t_wolf_3d *wolf)
{
    if (key == KEY_ESC)
    {
        mlx_destroy_image(wolf->mlx, wolf->window);
        exit(EXIT_SUCCESS);
    }
    if (key == KEY_UP || key == KEY_W)
        wolf->move.forward = 0;
    if (key == KEY_DOWN || key == KEY_S)
        wolf->move.back = 0;
    if (key == KEY_LEFT || key == KEY_A)
        wolf->move.left = 0;
    if (key == KEY_RIGHT || key == KEY_D)
        wolf->move.right = 0;
    return (1);
}

int		key_press(int key, t_wolf_3d *wolf)
{
    if (key == KEY_UP || key == KEY_W)
        wolf->move.forward = 1;
    if (key == KEY_DOWN || key == KEY_S)
        wolf->move.back = 1;
    if (key == KEY_LEFT || key == KEY_A)
        wolf->move.left = 1;
    if (key == KEY_RIGHT || key == KEY_D)
        wolf->move.right = 1;
    if (key == KEY_SPACEBAR)
        wolf->shot_flag = 1;
    return (1);
}
