/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:37:31 by rsatterf          #+#    #+#             */
/*   Updated: 2019/09/12 17:38:28 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_int_map2(t_wolf_3d *wolf, int i, int j)
{
	if ((i == 0) || (j == 0) || (i == (wolf->lines - 1))
		|| (j == (wolf->cols - 1)))
	{
		if (wolf->map[i][j] <= 0 || wolf->map[i][j] == 5)
			return (-1);
	}
	if ((wolf->map[i][j] == 5) && (wolf->flag == 0))
	{
		wolf->pos_x = i + 0.5;
		wolf->pos_y = j + 0.5;
		wolf->flag = 1;
		wolf->map[i][j] = 0;
	}
	else if ((wolf->map[i][j] == 5) && (wolf->flag == 1))
		return (-1);
	return (0);
}

int		check_int_map(t_wolf_3d *wolf)
{
	int	i;
	int	j;

	i = 0;
	wolf->pos_x = 0;
	wolf->pos_y = 0;
	wolf->flag = 0;
	while (i < wolf->lines)
	{
		j = 0;
		while (j < wolf->cols)
		{
			if (check_int_map2(wolf, i, j) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if ((wolf->pos_x == 0) || (wolf->pos_y == 0))
		return (-1);
	return (0);
}
