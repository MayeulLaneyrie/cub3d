/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:05:33 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/21 14:05:35 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	ft_check_fc(char *str, t_cub *cub)
{
	int	i;
	int	nb;
	int	virgule;

	i = 1;
	nb = 0;
	virgule = 0;
	if (str[1] != ' ')
		cub->error = 2;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != ',' && !(str[i] >= '0' && str[i] <= '9'))
			cub->error = 1;
		if (str[i] >= '0' && str[i] <= '9' && nb == 0)
			nb = 1;
		if (nb == 1 && str[i] == ',')
		{
			virgule++;
			nb = 0;
		}
		i++;
	}
	if (virgule != 2)
		cub->error = 1;
}

int	ft_fc(char *str, t_cub *cub)
{
	int	check;
	int	n;

	n = 24;
	cub->fc = 0;
	ft_check_fc(str, cub);
	while (str[cub->i] == ' ' || str[cub->i] == ',')
	{
		check = 0;
		cub->i++;
		while (str[cub->i] >= '0' && str[cub->i] <= '9')
		{
			check = check * 10 + str[cub->i] - 48;
			if (str[cub->i + 1] < '0' || str[cub->i] > '9')
			{
				n -= 8;
				cub->fc += check << n;
			}
			cub->i++;
		}
		if (check > 255 || check < 0)
			cub->error = 2;
	}
	return (cub->fc);
}

void	ft_color(char **str, t_cub *cub)
{
	int	i;

	i = 0;
	cub->i = 1;
	if (cub->nbligne > 0 && (cub->no == NULL || cub->so == NULL
			|| cub->ea == NULL || cub->we == NULL))
		cub->error = 3;
	if (*str[i] == 'F')
		cub->f = ft_fc(*str, cub);
	else if (*str[i] == 'C')
		cub->c = ft_fc(*str, cub);
}
