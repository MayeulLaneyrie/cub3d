/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/21 17:54:27 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	calc_max_w(char **map, int nbligne)
{
	int	ret;
	int	y;
	int	x;

	ret = 0;
	y = -1;
	while (++y < nbligne)
	{
		x = -1;
		while (map[y][++x])
			;
		if (x > ret)
			ret = x;
	}
	return (ret);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

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

	int	maxw = calc_max_w(cub->map, cub->nbligne);
	int	x;
	int	y;

	p.x1 = 20;
	p.y1 = 20;
	p.x2 = 10 * maxw;
	p.y2 = 10 * cub->nbligne;
	p.cr1 = 0x55ffffff;
	pcr_rect(cub->d, p);
	p.x2 = 10;
	p.y2 = 10;
	p.cr1 = 0xbb000000;
	y = -1;
	while (++y < cub->nbligne)
	{
		p.y1 = 20 + 10 * y;
		x = -1;
		while (cub->map[y][++x])
		{
			p.x1 = 20 + 10 * x;
			if (cub->map[y][x] != '1')
				pcr_rect(cub->d, p);
		}
	}
	p.x1 = 20 + 10 * cub->pos[X] - 3;
	p.y1 = 20 + 10 * cub->pos[Y] - 3;
	p.x2 = 6;
	p.y2 = 6;
	p.cr1 = 0xff0000;
	pcr_rect(cub->d, p);
	p.x1 += 3;
	p.y1 += 3;
	p.x2 = p.x1 + 20 * (cub->or_cam[X] + cub->or_plancam[X]);
	p.y2 = p.y1 + 20 * (cub->or_cam[Y] + cub->or_plancam[Y]);;
	pcr_line(cub->d, p);
	p.x2 = p.x1 + 20 * (cub->or_cam[X] - cub->or_plancam[X]);
	p.y2 = p.y1 + 20 * (cub->or_cam[Y] - cub->or_plancam[Y]);;
	pcr_line(cub->d, p);
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
		x++;
	}
	draw_hud(cub);
	pcr_display(cub->d);
	return (0);
}
