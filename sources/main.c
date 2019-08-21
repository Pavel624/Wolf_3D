/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbethany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:41:30 by nbethany          #+#    #+#             */
/*   Updated: 2019/08/21 23:41:35 by nbethany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static	int		close_app(void *param)
{
    (void)param;
    exit(0);
}

static	void	ft_error(char *msg, int i)
{
    ft_putstr(msg);
    exit(i);
}

static	void	init(t_wolf_3d *wolf)
{
    t_image *image;

    image = &wolf->image;
    wolf->mlx = mlx_init();
    wolf->window = mlx_new_window(wolf->mlx, WIDTH, HEIGHT, "Wolf_3d");
    image->image = mlx_new_image(wolf->mlx, WIDTH, HEIGHT);
    image->ptr = mlx_get_data_addr(image->image, &image->bpp,
                                   &image->line_s, &image->endian);
    image->bpp /= 8;
}

int main()
{
    t_wolf_3d *wolf;

    if (!(wolf = (t_wolf_3d*)malloc(sizeof(t_wolf_3d))))
        ft_error("Can't allocate enough memory for the structure", 0);
    init(wolf);
    mlx_hook(wolf->window, 17, 0L, close_app, &wolf);
    mlx_loop(wolf->mlx);
    return (0);
}
