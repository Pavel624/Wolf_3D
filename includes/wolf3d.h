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

# define WIDTH 640
# define HEIGHT 480

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
}               t_wolf_3d;

#endif
