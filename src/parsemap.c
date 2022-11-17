/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:38:37 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/17 17:51:34 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	floodfill(t_cub *cub, int x, int y, int overflow)
{
	if (x < 0 || y < 0 || !cub->map[y][x])
		ft_error("wrong map\n", 10, cub);
	if (overflow > 30000)
		ft_error("overflow\n", 8, cub);
	if (cub->map[y][x] != '0' && cub->map[y][x] != '2')
		return ;
	if (cub->map[y][x] == ' ' || cub->map[y][x] == 'X')
		return ;
	if (cub->map[y][x] == '0')
		cub->map[y][x] = ' ';
	if (cub->map[y][x] == '2')
		cub->map[y][x] = 'X';
	floodfill(cub, x + 1, y, overflow++);
	floodfill(cub, x - 1, y, overflow++);
	floodfill(cub, x, y + 1, overflow++);
	floodfill(cub, x, y - 1, overflow++);
}

void	orientation_start(t_cub *cub, int i, int j)
{
	if (cub->map[i][j] == 'N')
		cub->a = PI / 2;
	if (cub->map[i][j] == 'S')
		cub->a = 3 * PI / 2;
	if (cub->map[i][j] == 'E')
		cub->a = PI;
	if (cub->map[i][j] == 'W')
		cub->a = 0;
	cub->map[i][j] = '0';
	cub->pos[X] = j + 0.5;
	cub->pos[Y] = i + 0.5;
}

void	pos_start(t_cub *cub)
{
	int	i;
	int	j;
	int	compt;

	i = 0;
	compt = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S'
				|| cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{
				orientation_start(cub, i, j);
				compt++;
			}
			j++;
		}
		i++;
	}
	if (compt != 1 || cub->pos[X] == 0)
		ft_error("Nombre de position de depart incorect\n", 38, cub);
}

int	ft_stock_map(char *str, t_cub *cub)
{
	static int	i = 0;
	int			j;

	j = 0;
	cub->map[i] = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!cub->map[i])
		return (0);
	while (str[j])
	{
		if (str[j] == ' ')
			cub->map[i][j] = '1';
		else
			cub->map[i][j] = str[j];
		j++;
	}
	cub->map[i][j] = '\0';
	i++;
	return (0);
}

int	stock_map(char *fichier, t_cub *cub)
{
	int		fd;
	int		res;
	char	*str;

	res = 1;
	fd = open(fichier, O_RDONLY);
	cub->map = malloc(sizeof(char *) * (cub->nbligne + 1));
	if (!cub->map)
		return (0); //remplacer par ft error ?
	while (res != 0)
	{
		res = get_next_line(fd, &str, 1);
		if (str[0] == ' ' || str[0] == '1' || str[0] == '0' || str[0] == '2')
			ft_stock_map(str, cub);
		free(str);
	}
	cub->map[cub->nbligne] = 0;
	pos_start(cub);
	floodfill(cub, cub->pos[X] - 0.5, cub->pos[Y] - 0.5, 0);
	close(fd);
	return (0);
}

int	checkchar(char *str, t_cub *cub)
{
	int			i;
	static int	j = 0;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != ' '
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			return (0);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			j++;
		if (j > 1)
			cub->error = 8;
		i++;
	}
	return (1);
}

void	ft_map(char *str, t_cub *cub)
{
	static int	nbligne = 0;

	if (str[0] == ' ' || str[0] == '1' || str[0] == '0' || str[0] == '2')
		cub->flmap = 1;
	if (cub->flmap == 1)
	{
		if (cub->no == NULL || cub->so == NULL || cub->ea == NULL
			|| cub->we == NULL || cub->f == -1 || cub->c == -1)
			cub->error = 6;
		if (checkchar(str, cub) == 0)
			cub->error = 7;
		nbligne = nbligne + 1;
	}
	cub->nbligne = nbligne -1;
}
