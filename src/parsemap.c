/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:38:37 by shamizi           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/21 14:00:20 by shamizi          ###   ########.fr       */
=======
/*   Updated: 2022/11/21 13:21:28 by mlaneyri         ###   ########.fr       */
>>>>>>> b72ddb89c56d2115489006afbd861474c3a264b7
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
		return (0);
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
		if (!cub->texpath[no] || !cub->texpath[so] || !cub->texpath[ea]
			|| !cub->texpath[we] || cub->f == -1 || cub->c == -1)
			cub->error = 6;
		if (checkchar(str, cub) == 0)
			cub->error = 7;
		nbligne = nbligne + 1;
	}
	cub->nbligne = nbligne -1;
}
