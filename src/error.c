/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:19:04 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/23 14:45:13 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h" 

void	free_cub(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (cub->texpath[i])
			free(cub->texpath[i]);
		if (cub->d)
			pcr_destroy_img(cub->d, cub->texture[i]);
	}
	if (cub->map)
	{
		i = -1;
		while (cub->map[++i])
			free(cub->map[i]);
		free(cub->map);
	}
}

void	ft_error(char *str, int i, t_cub *cub)
{
	write(1, "Error\n", 6);
	write(1, str, i);
	free_cub(cub);
	pcr_destroy_disp(cub->d);
	exit(cub->error);
}
