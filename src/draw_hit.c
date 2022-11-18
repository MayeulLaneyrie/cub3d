/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:38:03 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/18 17:25:53 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	draw_hitline(t_cub *cub, t_hit hit, int x, t_image *img)
{
	int				start;
	int				end;
	int				lineheight;
//	static int		colors[4] = {8462323, 2352121, 123123132, 606060};
	static double	vfov = PI * FOV * WIN_H / (180 * WIN_W);
	int		color;
	(void)cub;
	lineheight = (int)(WIN_H / (hit.dist * 2 * tan(vfov / 2)));
	start = -lineheight / 2 + WIN_H / 2;
	if (start < 0)
		start = 0;
	end = lineheight / 2 + WIN_H / 2;
	if (end >= WIN_H)
		end = WIN_H - 1;

	//double step = 1.0 * img->px_h / lineheight;
	//hit.texx = (start - WIN_H / 2 + lineheight / 2) * step;
	//p.cr1 = colors[hit.face]; pcr_getpix(cub->d->img, x, y)
	while (start < end)
	{
		color = pcr_getpix(img, hit.texx * img->px_h, start / lineheight );
		pcr_pixel(cub->d, x, start, color);
	//	hit.texx += step;	
		start++;
	}

//	pcr_vline(cub->d, p);
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
