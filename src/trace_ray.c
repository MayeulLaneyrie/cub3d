/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:36:56 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/17 18:01:38 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	init_trace_ray(t_cub *cub, double *ray, double dd[3][2], int *mappos)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		mappos[i] = (int)cub->pos[i];
		if (!ray[i])
			dd[DDIST][i] = VERY_BIG;
		else
			dd[DDIST][i] = fabs(1 / ray[i]);
		dd[STEP][i] = fsgn(ray[i]);
		dd[SDIST][i] = dd[DDIST][i]
			* (dd[STEP][i] * mappos[i] - dd[STEP][i] * cub->pos[i]
				+ (dd[STEP][i] > 0));
	}
}

t_hit	*trace_ray(t_cub *cub, double *ray, t_hit *ret)
{
	int		i;
	double	dd[3][2];
	int		mappos[2];

	init_trace_ray(cub, ray, dd, mappos);
	while (1)
	{
		i = dd[SDIST][X] > dd[SDIST][Y];
		mappos[i] += dd[STEP][i];
		if (cub->map[mappos[Y]][mappos[X]] == '1')
			break ;
		dd[SDIST][i] += dd[DDIST][i];
	}
	ret->dist = dd[SDIST][i];
	if (i)
		ret->face = dd[STEP][i] < 0;
	else
		ret->face = 2 + (dd[STEP][i] > 0);
	return (ret);
}
