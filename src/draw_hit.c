/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:38:03 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/16 12:11:33 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	draw_hit(t_cub *cub, t_hit hit, int x)
{
	t_pcrparam 	p;
	(void)cub;
	(void)hit;
	(void)x;

	p.x1 = x;
	p.y1 = 0;
	p.y2 = WIN_H / 2 - 1;
	p.cr1 = cub->c;
	pcr_vline(cub->d, p);
	p.y1 = WIN_H / 2;
	p.y2 = WIN_H - 1;
	p.cr1 = cub->f;
	pcr_vline(cub->d, p);
	return (0);
}
