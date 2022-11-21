/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:38:03 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/21 20:35:59 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	draw_hitline(t_cub *cub, t_hit hit, int x, t_image *img)
{
	int				start;
	int				lineheight;
	static double	vfov = PI * FOV * WIN_H / (180 * WIN_W);
	int				i;

	lineheight = (int)(WIN_H / (hit.dist * 2 * tan(vfov / 2)));
	start = (WIN_H - lineheight) / 2;
	i = -1 - start * (start < 0);
	while (++i < lineheight + start * (start < 0))
	{
		if (start + i >= 0 || start + i < WIN_H)
			pcr_pixel(cub->d, x, start + i,
				pcr_getpix(img, hit.texx * img->px_w,
					img->px_h * i / lineheight));
	}
}

int	draw_hit(t_cub *cub, t_hit hit, int x)
{
	t_pcrparam	p;

	(void)hit;
	p.x1 = x;
	p.y1 = 0;
	p.y2 = WIN_H / 2 - 1;
	p.cr1 = cub->c;
	pcr_vline(cub->d, p);
	p.y1 = WIN_H / 2;
	p.y2 = WIN_H - 1;
	p.cr1 = cub->f;
	pcr_vline(cub->d, p);
	if (hit.dist > 0)
		draw_hitline(cub, hit, x, cub->texture[hit.face]);
	return (0);
}

/*
**	distance du point d'impact, variation de couleur et + distance proche
**	+ jaffiche dans t_hit ily a double dist = distance avant le hit
**
**	calculer la taille de la ligne a dessiner :
**		int lineHeight = int( h / PerpendiculaireWallDistance)
**	point le plus bas et le plus haut de cette ligne : 
**	int Drawstart = -lineHeight / 2 + h / 2;
**  if (drawstart < 0)
**  	drawstart = 0;
**	int drawEnd = lineheight / 2 + h /2;
**	if drawend >= h 
**	drawend = h - 1
*/
