/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:36:56 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/12/01 13:04:38 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	init_trace_ray(t_cub *cub, double *ray, double dd[3][2], int *mappos)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		mappos[i] = (int)cub->pos[i] - (cub->pos[i] < 0);
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

t_hit	*final_ray_calc(t_hit *ret)
{
	ret->texx -= floor(ret->texx);
	if (!(ret->face % 2))
		ret->texx = 1 - ret->texx;
	return (ret);
}

int	check_noclip(t_cub *cub, int mappos[2], double dd[3][2])
{
	int	out;

	if ((mappos[Y] < 0 && dd[STEP][Y] < 0)
		|| (mappos[Y] > cub->mapsize[Y] && dd[STEP][Y] > 0)
		|| (mappos[X] < 0 && dd[STEP][X] < 0)
		|| (mappos[X] > cub->mapsize[X] && dd[STEP][X] > 0))
		return (-1);
	out = (mappos[Y] < 0
			|| mappos[Y] > cub->mapsize[Y] - 1
			|| mappos[X] < 0
			|| mappos[X] > ft_strlen(cub->map[mappos[Y]]));
	return (out);
}

void	calc_face(t_hit *ret, double dd[3][2], int i)
{
	if (i)
		ret->face = dd[STEP][i] < 0;
	else
		ret->face = 2 + (dd[STEP][i] > 0);
}

t_hit	*trace_ray(t_cub *cub, double *ray, t_hit *ret)
{
	int		i;
	int		out;
	double	dd[3][2];
	int		mappos[2];

	init_trace_ray(cub, ray, dd, mappos);
	while (1)
	{
		i = dd[SDIST][X] > dd[SDIST][Y];
		mappos[i] += dd[STEP][i];
		out = check_noclip(cub, mappos, dd);
		if (out < 0)
			return (NULL);
		if (!out && cub->map[mappos[Y]][mappos[X]] == '1')
			break ;
		dd[SDIST][i] += dd[DDIST][i];
	}
	ret->dist = dd[SDIST][i];
	calc_face(ret, dd, i);
	if (i)
		ret->texx = cub->pos[X] + ret->dist * ray[X];
	else
		ret->texx = cub->pos[Y] + ret->dist * ray[Y];
	return (final_ray_calc(ret));
}
