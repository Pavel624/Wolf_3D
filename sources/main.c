/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:41:30 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/12 18:53:40 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				valid(t_wolf_3d *wolf)
{
	if (check_map_one(wolf) == -1 || check_map_two2(wolf) == -1 ||
		check_map_two(wolf) == -1 || check_int_map(wolf) == -1 ||
			check_map_one2(wolf) == -1)
		return (0);
	else
		return (1);
}

static	int		close_app(t_wolf_3d *wolf)
{
	free(wolf);
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

int				main(int argc, char **argv)
{
	t_wolf_3d *wolf;

	if (argc > 2)
		ft_error("too many parameters\n", 0);
	else if (argc == 1)
		ft_error("use map from maps\n", 0);
	if (!(wolf = (t_wolf_3d *)malloc(sizeof(t_wolf_3d))))
		ft_error("Can't allocate enough memory for the structure\n", 0);
	wolf->name = argv[1];
	if (!valid(wolf))
	{
		free(wolf);
		ft_error("error map\n", 0);
	}
	init(wolf);
	init_wolf(wolf);
	mlx_hook(wolf->window, 2, 1L << 0, key_press, wolf);
	mlx_hook(wolf->window, 3, 1L << 1, key_release, wolf);
	mlx_hook(wolf->window, 17, 1L << 17, close_app, wolf);
	mlx_loop_hook(wolf->mlx, loop, wolf);
	mlx_loop(wolf->mlx);
	return (0);
}
