/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/17 19:03:40 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	draw_hud(t_cub *cub)
{
	t_pcrparam	p;

	p.cr1 = 0xffffff;
	p.x1 = WIN_W / 2;
	p.y1 = WIN_H / 2 - WIN_H / 100;
	p.y2 = WIN_H / 2 + WIN_H / 100;
	pcr_vline(cub->d, p);
	p.x1 = WIN_W / 2 - WIN_H / 100;
	p.x2 = WIN_W / 2 + WIN_H / 100;
	p.y1 = WIN_H / 2;
	pcr_hline(cub->d, p);
	return (0);
}

int	frame(t_cub *cub)
{
	double	ray[2];
	t_hit	hit;
	int		x;

	cub->or_cam[X] = cos(cub->a);
	cub->or_cam[Y] = -sin(cub->a);
	cub->or_plancam[X] = -cub->or_cam[Y] * tan(PI * FOV / 360);
	cub->or_plancam[Y] = cub->or_cam[X] * tan(PI * FOV / 360);
	x = 0;
	while (x < WIN_W)
	{
		ray[X] = cub->or_cam[X] + (-1.0 + 2.0 * x / WIN_W) * cub->or_plancam[0];
		ray[Y] = cub->or_cam[Y] + (-1.0 + 2.0 * x / WIN_W) * cub->or_plancam[1];
		trace_ray(cub, ray, &hit);
		draw_hit(cub, hit, x);
		x += 1;
	}
	draw_hud(cub);
	pcr_display(cub->d);
	return (0);
}
