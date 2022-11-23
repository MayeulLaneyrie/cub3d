/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/23 21:23:55 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	text(t_cub *cub)
{
	t_pcrparam	p;
	static char	*txt[2] = {"PAUSE", "Press [ESC] to pause"};

	if (!cub->bonus)
		return ;
	p.x2 = 2;
	p.y2 = 2;
	p.cr1 = 0xffffff;
	p.cr2 = 0x000000;
	p.x1 = WIN_W / 2 - 30;
	p.y1 = WIN_H / 2 + 12;
	p.s = txt[0];
	if (cub->bonus > 1)
		pcr_txt_shadow(cub->d, p);
	p.x1 = 10;
	p.y1 = WIN_H - 10;
	p.s = txt[1];
	if (cub->bonus && cub->d->frame < 40)
		pcr_txt_shadow(cub->d, p);
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
	text(cub);
	return (0);
}
