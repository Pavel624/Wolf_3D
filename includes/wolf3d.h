/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:36:08 by nbethany          #+#    #+#             */
/*   Updated: 2019/08/21 23:36:12 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define WIDTH 1024
# define HEIGHT 1024

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct	s_image
{
    void		*image;
    char		*ptr;
    int			bpp;
    int			line_s;
    int			endian;
}				t_image;

typedef struct  s_wolf_3d
{
    void		*mlx;
    void		*window;
    t_image		image;
    char        *name;
    int         fd;
    int         cols;
    int         lines;
    double      pos_x;
    double      pos_y;
    double      dir_x;
    double      dir_y;
    double      plane_x;
    double      plane_y;
    double      camera_x;
    double      ray_dir_x;
    double      ray_dir_y;
    int         map_x;
    int         map_y;
    double      side_dist_x;
    double      side_dist_y;
    double      delta_dist_x;
    double      delta_dist_y;
    double      wall_dist;
    double      move_speed;
    double      rotate_speed;
    int         **map;
    int         flag;
    int         color;
}               t_wolf_3d;

void    ray_caster(t_wolf_3d *wolf);
void    init_wolf(t_wolf_3d *wolf);

int		key_trans(int key, t_wolf_3d *wolf);
int		key_down(int key);

#endif
