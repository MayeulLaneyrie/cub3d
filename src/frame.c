/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/23 16:01:46 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	pause_text(t_cub *cub)
{
	mlx_string_put(cub->d->mlx, cub->d->win, WIN_W / 2 - 30, WIN_H / 2 + 12,
		0xffffff, "PAUSE");
}

int	frame(t_cub *cub)
{
	double	ray[2];
	t_hit	hit;
	int		x;

	if (cub->bonus == 3)
		return (0);
	cub->or_cam[X] = cos(cub->a);
	cub->or_cam[Y] = -sin(cub->a);
	cub->or_plancam[X] = -cub->or_cam[Y] * tan(PI * FOV / 360);
	cub->or_plancam[Y] = cub->or_cam[X] * tan(PI * FOV / 360);
	x = 0;
	while (x < WIN_W)
	{
		ray[X] = cub->or_cam[X] + (-1.0 + 2.0 * x / WIN_W) * cub->or_plancam[0];
		ray[Y] = cub->or_cam[Y] + (-1.0 + 2.0 * x / WIN_W) * cub->or_plancam[1];
		if (!trace_ray(cub, ray, &hit))
			hit.dist = -1;
		draw_hit(cub, hit, x);
		x++;
	}
	draw_hud(cub);
	pcr_display(cub->d);
	if (cub->bonus > 1)
		pause_text(cub);
	return (0);
}
