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

int check_int_map2(t_wolf_3d *wolf, int i, int j)
{
    if (wolf->map[i][j] < 0)
        return (-1);
    if ((i == 0) || (j == 0) || (i == (wolf->lines - 1)) || (j == (wolf->cols - 1)))
    {
        if (wolf->map[i][j] == 0)
            return (-1);
    }
    if ((wolf->map[i][j] == 5) && (wolf->flag == 0))
    {
        wolf->pos_x = i;
        wolf->pos_y = j;
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
    if ((wolf->pos_x == 0) || (wolf->pos_x == 0))
        return (-1);
    return (0);
}

int check_map_one(t_wolf_3d *wolf)
{
    char	*line;
    int		i;
    int		k;

    wolf->fd = open(wolf->name, O_RDONLY);
    if ((k = get_next_line(wolf->fd, &line)) == 0)
        return (-1);
    close(wolf->fd);
    wolf->fd = open(wolf->name, O_RDONLY);
    while ((k = get_next_line(wolf->fd, &line)) > 0)
    {
        i = 0;
        while (line[i])
        {
            if (((line[i] >= 48) && (line[i] <= 57)) || (line[i] == ' ') || (line[i] == '\n'))
                i++;
            else
                return (-1);
        }
    }
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
        x++;
        free(tab[x]);
    }
    if (wolf->lines == 0)
        wolf->cols = x;
    else
    {
        if (x != wolf->cols)
            return (-1);
    }
    free(line);
    free(tab);
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
            return (-1);
    }
    close(wolf->fd);
    return ((a == -1) ? -1 : 0);
}

int		check_map_two(t_wolf_3d *wolf)
{
    int		a[3];
    char	*line;
    char	**tab;

    if ((check_map_two2(wolf) == -1) || ((wolf->map =(int **)malloc(sizeof(int *) * (wolf->lines))) == NULL))
        return (-1);
    a[1] = 0;
    wolf->fd = open(wolf->name, O_RDONLY);
    while ((a[0] = get_next_line(wolf->fd, &line)) > 0)
    {
        tab = ft_strsplit(line, ' ');
        wolf->map[a[1]] = (int*)malloc(sizeof(int) * (wolf->cols));
        a[2] = 0;
        while (tab[a[2]] != NULL)
        {
            wolf->map[a[1]][a[2]] = ft_atoi(tab[a[2]]);
            free(tab[a[2]]);
            a[2]++;
        }
        free(tab);
        a[1]++;
    }
    close(wolf->fd);
    return ((a[0] == -1) ? -1 : 0);
}

int     valid(t_wolf_3d *wolf)
{
    int	i;
    int	j;

    if ((check_map_one(wolf) == -1) || (check_map_two(wolf) == -1) || (check_int_map(wolf) == -1))
    {
        ft_putstr("error map\n");
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
        ft_error("error map\n", 0);
    init(wolf);
    init_wolf(wolf);
    ray_caster(wolf);
    mlx_key_hook(wolf->window, key_down, &wolf);
    mlx_hook(wolf->window, 2, (1L << 0), key_trans, wolf);
    mlx_hook(wolf->window, 17, 0L, close_app, &wolf);
    mlx_loop(wolf->mlx);
    return (0);
}
