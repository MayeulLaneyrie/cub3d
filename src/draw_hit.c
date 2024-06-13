/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:38:03 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/01/25 20:21:38 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	draw_hitline(t_cub *cub, t_hit hit, int x, t_image *img)
{
	int				start;
	int				line_h;
	static double	vfov = PI * FOV * WIN_H / (180 * WIN_W);
	int				i;

	line_h = (int)(WIN_H / (hit.dist * 2 * tan(vfov / 2)));
	start = (WIN_H - line_h) / 2;
	i = cub->d->frame % (V_IL * H_IL) / H_IL;
	while (i < WIN_H)
	{
		if (i >= start && i < WIN_H - start)
			pcr_pixel(cub->d, x, i,
				pcr_getpix(img, hit.texx * img->px_w,
					img->px_h * (i - start - 1) / line_h));
		else if (i < start)
			pcr_pixel(cub->d, x, i, cub->c);
		else
			pcr_pixel(cub->d, x, i, cub->f);
		i += V_IL;
	}
}

int	draw_hit(t_cub *cub, t_hit hit, int x)
{
	if (hit.dist > 0)
		draw_hitline(cub, hit, x, cub->texture[hit.face]);
	else
	{
		pcr_vline(cub->d,
			(t_pcr){.x1 = x, .y1 = 0, .y2 = (WIN_H / 2 - 1), .cr1 = cub->c});
		pcr_vline(cub->d,
			(t_pcr){.x1 = x, .y1 = (WIN_H / 2), .y2 = (WIN_H - 1), .cr1 = cub->f});
	}
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
