/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsatterf <rsatterf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:41:30 by nbethany          #+#    #+#             */
/*   Updated: 2019/09/11 20:38:01 by rsatterf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	free_double_arr(int **arr)
{
    int		i;

    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int check_int_map2(t_wolf_3d *wolf, int i, int j)
{
    if ((i == 0) || (j == 0) || (i == (wolf->lines - 1)) || (j == (wolf->cols - 1)))
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

int check_int_map(t_wolf_3d *wolf)
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

int check_map_one(t_wolf_3d *wolf)
{
    char	*line;
    int		i;

    wolf->fd = open(wolf->name, O_RDONLY);
    if (wolf->fd < 0)
    {
        close(wolf->fd);
        return (-1);
    }
    if ((get_next_line(wolf->fd, &line) <= 0))
    {
        ft_strdel(&line);
        return (-1);
    }
    ft_strdel(&line);
    close(wolf->fd);
    wolf->fd = open(wolf->name, O_RDONLY);
    while (get_next_line(wolf->fd, &line) > 0)
    {
        i = 0;
        while (line[i])
        {
            if (((line[i] >= 48) && (line[i] <= 57)) || (line[i] == ' ') || (line[i] == '\n') || (line[i] == '-'))
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

    wolf->map =(int **)malloc(sizeof(int *) * (wolf->lines));
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

int		valid(t_wolf_3d *wolf)
{
    int	i;
    int	j;

	if (check_map_one(wolf) == -1 || check_map_two2(wolf) == -1)
		return (0);
    if ((check_map_two(wolf) == -1) || (check_int_map(wolf) == -1))
    {
        free_double_arr(wolf->map);
        return (0);
    }
    else
    {
        printf("%s\n", "good");
        printf("%d\n", wolf->lines);
        printf("%d\n", wolf->cols);
        i = 0;
        while (i < wolf->lines)
        {
            j = 0;
            while (j < wolf->cols)
            {
                printf("%d ", wolf->map[i][j]);
                j++;
            }
            printf("%c", '\n');
            i++;
        }
        return (1);
    }
}

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

int main(int argc, char **argv)
{
    t_wolf_3d *wolf;

    if (argc > 2)
        ft_error("too many parameters\n", 0);
    else if (argc == 1)
        ft_error("use map from maps\n", 0);
    if (!(wolf = (t_wolf_3d *) malloc(sizeof(t_wolf_3d))))
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
