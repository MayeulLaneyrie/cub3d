/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/23 12:29:50 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	draw_mc(t_cub *cub)
{
	t_pcrparam	p;

	p.x1 = 10 + 10 * cub->pos[X] - 3;
	p.y1 = 10 + 10 * cub->pos[Y] - 3;
	p.x2 = 6;
	p.y2 = 6;
	p.cr1 = 0xff0000;
	pcr_rect(cub->d, p);
	p.x1 += 3;
	p.y1 += 3;
	p.x2 = p.x1 + 20 * (cub->or_cam[X] + cub->or_plancam[X]);
	p.y2 = p.y1 + 20 * (cub->or_cam[Y] + cub->or_plancam[Y]);
	pcr_line(cub->d, p);
	p.x2 = p.x1 + 20 * (cub->or_cam[X] - cub->or_plancam[X]);
	p.y2 = p.y1 + 20 * (cub->or_cam[Y] - cub->or_plancam[Y]);
	pcr_line(cub->d, p);
}

void	draw_map(t_cub *cub)
{
	t_pcrparam	p;
	int			x;
	int			y;

	p.x1 = 10;
	p.y1 = 10;
	p.x2 = 10 * cub->mapsize[X];
	p.y2 = 10 * cub->mapsize[Y];
	p.cr1 = 0x80ffffff;
	pcr_rect(cub->d, p);
	p.x2 = 10;
	p.y2 = 10;
	p.cr1 = 0xa0000000;
	y = -1;
	while (++y < cub->mapsize[Y])
	{
		p.y1 = 10 + 10 * y;
		x = -1;
		while (cub->map[y][++x])
		{
			p.x1 = 10 + 10 * x;
			if (cub->map[y][x] != '1')
				pcr_rect(cub->d, p);
		}
	}
}

void	draw_cursor(t_cub *cub)
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
}

void	draw_pause(t_cub *cub)
{
	t_pcrparam	p;

	if (cub->bonus < 2)
		return ;
	cub->bonus = 3;
	p.x1 = 0;
	p.y1 = 0;
	p.x2 = WIN_W;
	p.y2 = WIN_H;
	p.cr1 = 0x60000000;
	pcr_rect(cub->d, p);
}

/*
**	@92:
**	mlx_mouse_show(cub->d->mlx, cub->d->win);
*/

void	draw_hud(t_cub *cub)
{
	if (!cub->bonus)
		return ;
	draw_cursor(cub);
	draw_map(cub);
	draw_mc(cub);
	draw_pause(cub);
}
