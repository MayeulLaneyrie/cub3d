/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2023/01/25 20:22:28 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	draw_mc(t_cub *cub)
{
	t_pcr	p;

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
	t_pcr	p;
	int		x;
	int		y;

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
				p.cr1 = 0xa0000000;
			else
				p.cr1 = 0x80ffffff;
			if (cub->map[y][x] == ' ' || cub->map[y][x] == '1')
				pcr_rect(cub->d, p);
		}
	}
}

void	draw_cursor(t_cub *cub)
{
	t_pcr	p;

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
	int	i;

	if (cub->bonus < 2)
		return ;
	cub->bonus = 3;
	i = cub->d->frame % V_IL;
	while (i < WIN_H)
	{
		pcr_rect(cub->d,
			(t_pcr){.x1 = 0, .y1 = i, .x2 = WIN_W, .y2 = i, .cr1 = 0x60000000});
		i += V_IL;
	}
	/*
	p.x1 = 0;
	p.y1 = 0;
	p.x2 = WIN_W;
	p.y2 = WIN_H;
	p.cr1 = 0x60000000;
	pcr_rect(cub->d, p);
	*/
	mouse(cub->d, 1);
}

/*
**	@92:
**	mlx_mouse_show(cub->d->mlx, cub->d->win);
*/

void	draw_hud(t_cub *cub)
{
	if (!cub->bonus)
		return ;
	if (cub->bonus < 2)
		draw_cursor(cub);
	else
		draw_pause(cub);
	if (cub->minimap)
	{
		draw_map(cub);
		draw_mc(cub);
	}
}
