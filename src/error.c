/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:19:04 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/17 14:04:24 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h" 

void	free_cub(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->no)
		free(cub->no);
	if (cub->so)
		free(cub->so);
	if (cub->ea)
		free(cub->ea);
	if (cub->we)
		free(cub->we);
	if (cub->map)
	{
		while (cub->map[i])
		{
			free(cub->map[i]);
			i++;
		}
		free(cub->map);
	}
}

void	ft_error(char *str, int i/*ajouter les stucture ici*/)
{
	write(1, "Error\n", 6);
	write(1, str, i);
	//free_cub(cub);
	exit(EXIT_FAILURE);
}
