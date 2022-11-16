/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:38:03 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/16 13:56:54 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

void	draw_hitline(t_cub *cub, t_hit hit, t_pcrparam p)
{
	(void)hit;
	int start;
	int end;
	int lineHeight = (int)(WIN_H / hit->dist);

	start = -lineHeight / 2 + WIN_H / 2;
	if (start < 0)
		start = 0;
	end = lineHeight / 2 + WIN_H / 2;
	if (end >= WIN_H)
		end = WIN_H - 1;
	p.cr1 = 8462323; //couleur du mur
	p.y1 = start; // debut de la ligne de pixel
	p.y2 = end; // fin de la ligne de pixel
	pcr_vline(cub->d, p);
}

int	draw_hit(t_cub *cub, t_hit hit, int x)
{
	t_pcrparam 	p;
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
	draw_hitline(cub, hit, p);
	return (0);
}

//distance du point d'impact, variation de couleur et + distance proche + jaffiche
//dans t_hit ily a double dist = distance avant le hit

//calculer la taille de la ligne a dessiner : int lineHeight = int( h / PerpendiculaireWallDistance)
//point le plus bas et le plus haut de cette ligne : 
/*int Drawstart = -lineHeight / 2 + h / 2;
  if (drawstart < 0)
  	drawstart = 0;
int drawEnd = lineheight / 2 + h /2;
if drawend >= h 
	drawend = h - 1
  */
