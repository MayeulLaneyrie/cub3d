/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:38:37 by shamizi           #+#    #+#             */
/*   Updated: 2022/12/01 13:28:51 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

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
			cub->map[i][j] = '.';
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
	cub->map = malloc(sizeof(char *) * (cub->mapsize[Y] + 1));
	if (!cub->map)
		return (0);
	while (res != 0)
	{
		res = get_next_line(fd, &str, 1);
		if (str[0] == ' ' || str[0] == '1' || str[0] == '0')
			ft_stock_map(str, cub);
		free(str);
	}
	cub->map[cub->mapsize[Y]] = 0;
	pos_start(cub);
	floodfill(cub, cub->pos[X] - 0.5, cub->pos[Y] - 0.5, 0);
	close(fd);
	return (0);
}

int	checkchar(char *str, t_cub *cub)
{
	int			i;
	static int	j = 0;
	static int	k = 0;

	i = 0;
	if (!str[0])
		k++;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != ' ' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W' && !str[0])
			return (0);
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			j++;
		if (j > 1)
			cub->error = 8;
		if (k > 0 && (str[i] == '1' || str[i] == '0' || str[i] == ' '))
			cub->error = 9;
		i++;
	}
	return (1);
}

void	ft_map(char *str, t_cub *cub)
{
	static int	nbligne = 0;
	

	if (str[0] == ' ' || str[0] == '1' || str[0] == '0')
		cub->flmap = 1;
	if (cub->flmap)
	{
		if (!cub->texpath[no] || !cub->texpath[so] || !cub->texpath[ea]
			|| !cub->texpath[we] || cub->f == -1 || cub->c == -1)
			cub->error = 6;
		if (!checkchar(str, cub))
			cub->error = 7;
		if (ft_strlen(str) > cub->mapsize[X])
			cub->mapsize[X] = ft_strlen(str);
		if (str[0] == '1' || str[0] == ' ' || str[0] == '0')
			nbligne++;
	}
	cub->mapsize[Y] = nbligne;
}
