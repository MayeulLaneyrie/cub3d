/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:34:23 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/21 17:50:46 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pcr.h"

int	pcr_getpix(t_image *img, int x, int y)
{
	int				ret;
	unsigned char	*src;

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
	unsigned char	*dst;
	unsigned char	sw;
	unsigned char	alpha;

	if (x < 0 || y < 0 || x >= d->w || y >= d->h)
		return (-1);
	sw = d->frame % 2;
	dst = d->img[sw]->addr + y * d->img[sw]->w + x * d->img[sw]->opp;
	alpha = cr >> 24;
	if (!d->img[sw]->endn)
		*(unsigned int *)dst = cr;
	else
	{
		dst[1] = (cr >> 16) & 0xff;
		dst[2] = (cr >> 8) & 0xff;
		dst[3] = cr & 0xff;
	}
	return (0);
}

int	pcr_pixel_alpha(t_disp *d, int x, int y, int cr)
{
	unsigned char	*dst;
	unsigned char	sw;
	unsigned char	alpha;

	if (x < 0 || y < 0 || x >= d->w || y >= d->h)
		return (-1);
	sw = d->frame % 2;
	dst = d->img[sw]->addr + y * d->img[sw]->w + x * d->img[sw]->opp;
	alpha = cr >> 24;
	if (!d->img[sw]->endn)
	{
		dst[2] = dst[2] * alpha / 256 + (cr >> 16 & 0xff) * (256 - alpha) / 256;
		dst[1] = dst[1] * alpha / 256 + (cr >> 8 & 0xff) * (256 - alpha) / 256;
		dst[0] = dst[0] * alpha / 256 + (cr & 0xff) * (256 - alpha) / 256;
	}
	else
	{
		dst[0] = cr >> 24;
		dst[1] = (cr >> 16) & 0xff;
		dst[2] = (cr >> 8) & 0xff;
		dst[3] = cr & 0xff;
	}
	return (0);
}
