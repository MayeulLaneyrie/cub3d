/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_line_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:34:23 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/18 16:11:51 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pcr.h"

int	pcr_getpix(t_image *img, int x, int y)
{
	int		ret;
	char	*src;

	if (x < 0 || x >= img->px_w || y < 0 || y >= img->px_h)
		return (0);
	src = img->addr + y * img->w + x * img->opp;
	ret = 0;
	if (!img->endn)
		ret = *(unsigned int *)src;
	else
	{
		ret += src[0] << 24;
		ret += src[1] << 16;
		ret += src[2] << 8;
		ret += src[3];
	}
	return (ret);
}

int	pcr_pixel(t_disp *d, int x, int y, int cr)
{
	char	*dst;
	int		sw;

	if (x < 0 || y < 0 || x >= d->w || y >= d->h)
		return (-1);
	sw = d->frame % 2;
	dst = d->img[sw]->addr + y * d->img[sw]->w + x * d->img[sw]->opp;
	if (!d->img[sw]->endn)
		*(unsigned int *)dst = cr;
	else
	{
		dst[0] = cr >> 24;
		dst[1] = (cr >> 16) & 0xff;
		dst[2] = (cr >> 8) & 0xff;
		dst[3] = cr & 0xff;
	}
	return (0);
}

int	abs(int x)
{
	if (x > 0)
		return (x);
	return (-x);
}

int	fsgn(double d)
{
	if (d < 0)
		return (-1);
	return (1);
}

int	pcr_fade(float t, int cr1, int cr2)
{
	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	return (pcr_add(pcr_mul(1 - t, cr1), pcr_mul(t, cr2)));
}
