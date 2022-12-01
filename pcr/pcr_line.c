/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:34:23 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/16 12:04:49 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pcr.h"

static int	y_plus(t_disp *d, t_pcrparam p, int dx, int dy)
{
	int	t;

	t = -1;
	while (++t <= dy)
		pcr_pixel(d, p.x1 + t * dx / dy, p.y1 + t, p.cr1);
	return (0);
}

static int	y_minus(t_disp *d, t_pcrparam p, int dx, int dy)
{
	int	t;

	t = 1;
	while (--t >= dy)
		pcr_pixel(d, p.x1 + t * dx / dy, p.y1 + t, p.cr1);
	return (0);
}

static int	x_plus(t_disp *d, t_pcrparam p, int dx, int dy)
{
	int	t;

	t = -1;
	while (++t <= dx)
		pcr_pixel(d, p.x1 + t, p.y1 + t * dy / dx, p.cr1);
	return (0);
}

static int	x_minus(t_disp *d, t_pcrparam p, int dx, int dy)
{
	int	t;

	t = 1;
	while (--t >= dx)
		pcr_pixel(d, p.x1 + t, p.y1 + t * dy / dx, p.cr1);
	return (0);
}

int	pcr_line(t_disp *d, t_pcrparam p)
{
	int	dx;
	int	dy;

	if ((p.x1 < 0 && p.x2 < 0) || (p.x1 > d->w && p.x2 > d->w)
		|| (p.y1 < 0 && p.y2 < 0) || (p.y1 > d->h && p.y2 > d->h))
		return (-1);
	dx = p.x2 - p.x1;
	dy = p.y2 - p.y1;
	if (abs(dy) > abs(dx))
	{
		if (dy > 0)
			y_plus(d, p, dx, dy);
		else
			y_minus(d, p, dx, dy);
	}
	else if (dx)
	{
		if (dx > 0)
			x_plus(d, p, dx, dy);
		else
			x_minus(d, p, dx, dy);
	}
	return (0);
}
