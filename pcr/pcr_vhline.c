/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_vhline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:34:23 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/01/25 17:40:33 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pcr.h"

int	pcr_vline(t_disp *d, t_pcr p)
{
	int	t;

	t = p.y1 - 1;
	while (++t <= p.y2)
		pcr_pixel(d, p.x1, t, p.cr1);
	return (0);
}

int	pcr_hline(t_disp *d, t_pcr p)
{
	int	t;

	t = p.x1 - 1;
	while (++t <= p.x2)
		pcr_pixel(d, t, p.y1, p.cr1);
	return (0);
}
