/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/12/01 13:29:49 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

static void	aux(t_cub *cub)
{
	cub->flmap = 0;
	cub->a = 0;
	cub->d = NULL;
	cub->map = NULL;
	cub->minimap = 0;
}

void	ft_init(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 7)
		cub->key_buffer[i] = 0;
	i = -1;
	while (++i < 4)
	{
		cub->texpath[i] = NULL;
		cub->texture[i] = NULL;
		cub->pos[i / 2] = 0;
		cub->or_cam[i / 2] = 0;
		cub->or_plancam[i / 2] = 0;
		cub->mapsize[i / 2] = 0;
	}
	cub->update = 0;
	cub->i = 0;
	cub->error = 0;
	cub->fc = 0;
	cub->f = -1;
	cub->c = -1;
	aux(cub);
}
