/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:01:43 by shamizi           #+#    #+#             */
/*   Updated: 2022/12/01 13:13:23 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	floodfill(t_cub *cub, int x, int y, int overflow)
{
	if (!cub->map[y]) 
		ft_error("wrong map\n", 10, cub);
	if (x > ft_strlen(cub->map[y]))
		ft_error("Wrong map\n", 10, cub);
	if (x < 0 || y < 0 || !cub->map[y][x] || cub->map[y][x] == '.')
		ft_error("wrong map\n", 10, cub);
	if (overflow > 30000)
		ft_error("overflow\n", 8, cub);
	if (cub->map[y][x] != '0')
		return ;
	if (cub->map[y][x] == ' ')
		return ;
	if (cub->map[y][x] == '0')
		cub->map[y][x] = ' ';
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
