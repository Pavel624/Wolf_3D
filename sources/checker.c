/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:34:53 by rsatterf          #+#    #+#             */
/*   Updated: 2019/09/12 17:38:36 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_map_one2(t_wolf_3d *wolf)
{
	char *line;

	wolf->fd = open(wolf->name, O_RDONLY);
	if (wolf->fd < 0)
	{
		close(wolf->fd);
		return (-1);
	}
	if ((get_next_line(wolf->fd, &line) < 0))
	{
		ft_strdel(&line);
		return (-1);
	}
	ft_strdel(&line);
	close(wolf->fd);
	return (0);
}

int		check_map_one(t_wolf_3d *wolf)
{
	char	*line;
	int		i;

	wolf->fd = open(wolf->name, O_RDONLY);
	while (get_next_line(wolf->fd, &line) > 0)
	{
		i = 0;
		while (line[i])
		{
			if (((line[i] >= 48) && (line[i] <= 57)) ||
				(line[i] == ' ') || (line[i] == '\n') || (line[i] == '-'))
				i++;
			else
			{
				ft_strdel(&line);
				return (-1);
			}
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(wolf->fd);
	return (0);
}

int		check_map_two3(t_wolf_3d *wolf, char *line)
{
	int		x;
	char	**tab;

	x = 0;
	tab = ft_strsplit(line, ' ');
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	if (wolf->lines == 0)
		wolf->cols = x;
	else
	{
		if (x != wolf->cols)
		{
			free(tab);
			return (-1);
		}
	}
	free(tab);
	free(line);
	wolf->lines++;
	return (0);
}

int		check_map_two2(t_wolf_3d *wolf)
{
	char	*line;
	int		a;

	wolf->lines = 0;
	wolf->cols = 0;
	wolf->fd = open(wolf->name, O_RDONLY);
	while ((a = get_next_line(wolf->fd, &line)) > 0)
	{
		if (check_map_two3(wolf, line) == -1)
		{
			ft_strdel(&line);
			return (-1);
		}
	}
	close(wolf->fd);
	return ((a == -1) ? -1 : 0);
}

int		check_map_two(t_wolf_3d *wolf)
{
	int		a[3];
	char	*line;
	char	**tab;

	wolf->map = (int **)malloc(sizeof(int *) * (wolf->lines));
	a[1] = 0;
	wolf->fd = open(wolf->name, O_RDONLY);
	while ((a[0] = get_next_line(wolf->fd, &line)) > 0)
	{
		tab = ft_strsplit(line, ' ');
		wolf->map[a[1]] = (int*)malloc(sizeof(int) * (wolf->cols));
		a[2] = 0;
		while (tab[a[2]])
		{
			wolf->map[a[1]][a[2]] = ft_atoi(tab[a[2]]);
			free(tab[a[2]]);
			a[2]++;
		}
		free(tab);
		ft_strdel(&line);
		a[1]++;
	}
	ft_strdel(&line);
	close(wolf->fd);
	return ((a[0] == -1) ? -1 : 0);
}
