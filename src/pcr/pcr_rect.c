/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:56:18 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/21 17:52:49 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pcr.h"

int	pcr_rect(t_disp *d, t_pcrparam p)
{
	int	x;
	int	y;

	y = -1;
	if (p.cr1 >> 24)
	{
		while (++y < p.y2)
		{
			x = -1;
			while (++x < p.x2)
				pcr_pixel_alpha(d, p.x1 + x, p.y1 + y, p.cr1);
		}
	}
	else
	{
		while (++y < p.y2)
		{
			x = -1;
			while (++x < p.x2)
				pcr_pixel(d, p.x1 + x, p.y1 + y, p.cr1);
		}
	}
	return (0);
}
