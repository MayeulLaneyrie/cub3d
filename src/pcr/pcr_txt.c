/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_txt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnr <mayeul.lnr@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:07:58 by lnr               #+#    #+#             */
/*   Updated: 2022/11/23 21:23:19 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pcr.h"

int	pcr_txt(t_disp *d, t_pcrparam p)
{
	mlx_string_put(d->mlx, d->win, p.x1, p.y1, p.cr1, p.s);
	return (0);
}

int	pcr_txt_shadow(t_disp *d, t_pcrparam p)
{
	mlx_string_put(d->mlx, d->win, p.x1 + p.x2, p.y1 + p.y2, p.cr2, p.s);
	mlx_string_put(d->mlx, d->win, p.x1, p.y1, p.cr1, p.s);
	return (0);
}
