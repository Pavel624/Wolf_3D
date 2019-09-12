/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:57:17 by rsatterf          #+#    #+#             */
/*   Updated: 2019/09/12 17:58:18 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_textures2(t_wolf_3d *wolf)
{
	int	a;
	int	b;
	int	pistol_res_width;
	int	pistol_res_height;

	pistol_res_height = 317;
	pistol_res_width = 228;
	a = 512;
	b = 512;
	wolf->tex[4].image = mlx_xpm_file_to_image(wolf->mlx,
		"textures/sky.xpm", &a, &b);
	wolf->tex[4].ptr = mlx_get_data_addr(wolf->tex[4].image,
		&wolf->tex[4].bpp, &wolf->tex[4].line_s, &wolf->tex[4].endian);
	wolf->tex[4].bpp /= 8;
	wolf->pistol[0].image = mlx_xpm_file_to_image(wolf->mlx,
		"textures/gun_1.xpm", &pistol_res_width, &pistol_res_height);
	wolf->pistol[1].image = mlx_xpm_file_to_image(wolf->mlx,
		"textures/gun_2.xpm", &pistol_res_width, &pistol_res_height);
	wolf->pistol[2].image = mlx_xpm_file_to_image(wolf->mlx,
		"textures/gun_3.xpm", &pistol_res_width, &pistol_res_height);
	wolf->pistol[3].image = mlx_xpm_file_to_image(wolf->mlx,
		"textures/gun_4.xpm", &pistol_res_width, &pistol_res_height);
}

void	load_textures(t_wolf_3d *wolf)
{
	int	tex_width;
	int	tex_height;

	tex_height = 64;
	tex_width = 64;
	wolf->tex[0].image = mlx_xpm_file_to_image(wolf->mlx,
		"textures/stone.xpm", &tex_width, &tex_height);
	wolf->tex[0].ptr = mlx_get_data_addr(wolf->tex[0].image,
		&wolf->tex[0].bpp, &wolf->tex[0].line_s, &wolf->tex[0].endian);
	wolf->tex[0].bpp /= 8;
	wolf->tex[1].image = mlx_xpm_file_to_image(wolf->mlx,
		"textures/sand.xpm", &tex_width, &tex_height);
	wolf->tex[1].ptr = mlx_get_data_addr(wolf->tex[1].image,
		&wolf->tex[1].bpp, &wolf->tex[1].line_s, &wolf->tex[1].endian);
	wolf->tex[1].bpp /= 8;
	wolf->tex[2].image = mlx_xpm_file_to_image(wolf->mlx,
		"textures/wood.xpm", &tex_width, &tex_height);
	wolf->tex[2].ptr = mlx_get_data_addr(wolf->tex[2].image,
		&wolf->tex[2].bpp, &wolf->tex[2].line_s, &wolf->tex[2].endian);
	wolf->tex[2].bpp /= 8;
	wolf->tex[3].image = mlx_xpm_file_to_image(wolf->mlx,
		"textures/mossy.xpm", &tex_width, &tex_height);
	wolf->tex[3].ptr = mlx_get_data_addr(wolf->tex[3].image,
		&wolf->tex[3].bpp, &wolf->tex[3].line_s, &wolf->tex[3].endian);
	wolf->tex[3].bpp /= 8;
}

void	pistol_animation(t_wolf_3d *wolf)
{
	if (wolf->shot_frames >= 11)
		mlx_put_image_to_window(wolf->mlx, wolf->window,
			wolf->pistol[1].image, (WIDTH - 100) / 2, HEIGHT - 300);
	else if (wolf->shot_frames >= 6 && wolf->shot_frames < 11)
		mlx_put_image_to_window(wolf->mlx, wolf->window,
			wolf->pistol[2].image, (WIDTH - 100) / 2, HEIGHT - 300);
	else if (wolf->shot_frames >= 3 && wolf->shot_frames < 6)
		mlx_put_image_to_window(wolf->mlx, wolf->window,
			wolf->pistol[3].image, (WIDTH - 100) / 2, HEIGHT - 300);
	else if (wolf->shot_frames == 2)
		mlx_put_image_to_window(wolf->mlx, wolf->window,
			wolf->pistol[3].image, (WIDTH - 100) / 2, HEIGHT - 300);
	wolf->shot_frames--;
	if (wolf->shot_frames == 1)
	{
		wolf->shot_frames = 16;
		wolf->shot_flag = 0;
	}
}

void	animate_pistol(t_wolf_3d *wolf)
{
	if (wolf->shot_flag == 0)
		mlx_put_image_to_window(wolf->mlx, wolf->window,
			wolf->pistol[0].image, (WIDTH - 100) / 2, HEIGHT - 300);
	else if (wolf->shot_flag == 1)
	{
		if (wolf->shot_frames == 16)
			OS_VER == 0 ? system("afplay -v 0.65 audio/gun_shot.wav &") :
				system("paplay --volume 35000 audio/gun_shot.wav");
		pistol_animation(wolf);
	}
}
