/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:36:56 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/16 13:55:04 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

t_hit	*trace_ray(t_cub *cub, double *ray, t_hit *ret)
{
	int		i;
	double	ddist[2];
	double	sdist[2];
	double	step[2];
	int		mappos[2];

	i = -1;
	while (++i < 2)
	{
		mappos[i] = cub->pos[i];
		if (!ray[i])
			ddist[i] = VERY_BIG;
		else
			ddist[i] = fabs(1.0 / ray[i]);
		step[i] = fsgn(ray[i]);
		sdist[i] = ddist[i]
			* (step[i] * mappos[i] - step[i] * cub->pos[i] + (step[i] > 0));
	}

	while (1)
	{
		i = sdist[X] < sdist[Y];
		mappos[i] += step[i];
		ret->face = i;
		if (cub->map[mappos[X]][mappos[Y]] == '1')
			break ;
		sdist[i] += ddist[i];
	}
	ret->dist = sdist[ret->face];
	if (ret->face)
		ret->face = step[ret->face] < 0;
	else
		ret->face = 2 + step[ret->face] > 0;
	return (ret);
}
