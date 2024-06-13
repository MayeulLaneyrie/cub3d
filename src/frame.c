/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2023/01/25 20:21:57 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	norme(t_cub *cub, t_pcr p)
{
	static char	*txt[2] = {"Press [ESC] to pause",
		"Press [M] to display minimap"};
	static int	done[2] = {0};

	if (cub->bonus > 1)
		done[0] = 1;
	p.x1 = 10;
	p.y1 = WIN_H - 10;
	p.s = txt[1];
	if (cub->minimap)
		done[1] = 1;
	if (!cub->minimap && cub->d->frame < 60 && !done[1])
		pcr_txt_shadow(cub->d, p);
	p.y1 -= 28 * (!cub->minimap && !done[1]);
	p.s = txt[0];
	if (cub->bonus == 1 && cub->d->frame < 60 && !done[0])
		pcr_txt_shadow(cub->d, p);
}

void	text(t_cub *cub)
{
	t_pcr		p;
	static char	*txt = "PAUSE";

	if (!cub->bonus)
		return ;
	p.x2 = 2;
	p.y2 = 2;
	p.cr1 = 0xffffff;
	p.cr2 = 0x000000;
	p.x1 = WIN_W / 2 - 30;
	p.y1 = WIN_H / 2 + 12;
	p.s = txt;
	if (cub->bonus > 1)
		pcr_txt_shadow(cub->d, p);
	norme(cub, p);
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
	x = cub->d->frame % H_IL;
	while (x < WIN_W)
	{
		ray[X] = cub->or_cam[X] + (-1.0 + 2.0 * x / WIN_W) * cub->or_plancam[0];
		ray[Y] = cub->or_cam[Y] + (-1.0 + 2.0 * x / WIN_W) * cub->or_plancam[1];
		if (!trace_ray(cub, ray, &hit))
			hit.dist = -1;
		draw_hit(cub, hit, x);
		x += H_IL;
	}
	draw_hud(cub);
	pcr_display(cub->d);
	text(cub);
	return (0);
}
