/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:36:56 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/16 14:42:12 by mlaneyri         ###   ########.fr       */
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

	printf("%f ;;; %f\n", ray[X], ray[Y]);
	i = -1;
	while (++i < 2)
	{
		mappos[i] = (int)cub->pos[i];
		if (!ray[i])
		{
			printf("COUCOU\n");
			ddist[i] = VERY_BIG;
		}
		else
			ddist[i] = fabs(1 / ray[i]);
		step[i] = fsgn(ray[i]);
		sdist[i] = ddist[i]
			* (step[i] * mappos[i] - step[i] * cub->pos[i] + (step[i] > 0));
	}
	printf("%f ;;; %f\n", ddist[X], ddist[Y]);
	while (1)
	{
		i = sdist[X] > sdist[Y];
		printf("%d  %d    %d\n", mappos[X], mappos[Y], i);
		mappos[i] += step[i];
		//printf("---> %f\n", sdist[i]);
		if (cub->map[mappos[Y]][mappos[X]] == '1')
			break ;
		sdist[i] += ddist[i];
	}
	printf("==> %d  %d (%f)\n\n", mappos[X], mappos[Y], sdist[i]);
	ret->dist = sdist[i];
	if (i)
		ret->face = step[i] < 0;
	else
		ret->face = 2 + step[i] > 0;
	return (ret);
}
