/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:36:08 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/04 17:41:56 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/libft.h"
# include <math.h>
# ifdef __APPLE__
# include <mlx.h>
#define OS_VER 0
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_D 2
# define KEY_A 0
# define KEY_S 1
# define KEY_SPACEBAR 49
#elif __linux__
# define OS_VER 1
# include "../minilibx/mlx.h"
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_D 100
# define KEY_A 97
# define KEY_S 115
# define KEY_SPACEBAR 32
#endif

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
#include <sys/types.h>

# define WIDTH 1024
# define HEIGHT 768
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct	s_image
{
    void		*image;
    char		*ptr;
    int			bpp;
    int			line_s;
    int			endian;
}				t_image;

typedef struct  s_move
{
    int forward;
    int back;
    int right;
    int left;
}               t_move;

typedef struct  s_wolf_3d
{
    int			er;
    void		*mlx;
    void		*window;
    t_image		image;
    t_image     tex[6];
    t_image     pistol[4];
    t_move      move;
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
    int         tex_num;
    int         d;
    int         line_height;
    int         tex_y;
    double      wall_x;
    int         tex_x;
    int         draw_start;
    int         draw_end;
    double      current_floor_x;
    double      current_floor_y;
    int         floor_tex_x;
    int         floor_tex_y;
    double      weight;
    int         flag;
    int         color;
    int         shot_flag;
    int         shot_frames;
}               t_wolf_3d;

void    ray_caster(t_wolf_3d *wolf);
void    init_wolf(t_wolf_3d *wolf);
void    load_textures(t_wolf_3d *wolf);

int		key_press(int key, t_wolf_3d *wolf);
int		key_release(int key, t_wolf_3d *wolf);

void movement(t_wolf_3d *wolf);
int loop(t_wolf_3d *wolf);

#endif
