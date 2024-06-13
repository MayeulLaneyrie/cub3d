/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:33:07 by mlaneyri          #+#    #+#             */
/*   Updated: 2023/01/25 20:29:55 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pcr.h"

t_image	*pcr_init_img(t_disp *d, int w, int h)
{
	t_image	*ret;

	ret = malloc(sizeof(t_image));
	if (!ret)
		return (NULL);
	ret->img = mlx_new_image(d->mlx, w, h);
	ret->addr = (unsigned char *)mlx_get_data_addr(ret->img, &(ret->bpp),
			&(ret->w), &(ret->endn));
	ret->opp = ret->bpp / 8;
	ret->px_w = w;
	ret->px_h = h;
	return (ret);
}

t_image	*pcr_load_img(t_disp *d, char *path)
{
	t_image	*ret;

	ret = malloc(sizeof(t_image));
	if (!ret)
		return (NULL);
	ret->img = mlx_xpm_file_to_image(d->mlx, path, &(ret->px_w), &(ret->px_h));
	if (!ret->img)
	{
		free(ret);
		return (NULL);
	}
	ret->addr = (unsigned char *)mlx_get_data_addr(ret->img, &(ret->bpp),
			&(ret->w), &(ret->endn));
	ret->opp = ret->bpp / 8;
	return (ret);
}

t_disp	*pcr_init_disp(int w, int h, char *s)
{
	t_disp	*ret;

	ret = malloc(sizeof(t_disp));
	if (!ret)
		return (NULL);
	ret->frame = 0;
	ret->w = w;
	ret->h = h;
	ret->img[0] = NULL;
	ret->img[1] = NULL;
	ret->win = NULL;
	ret->mlx = mlx_init();
	if (!ret->mlx)
		return (pcr_destroy_disp(ret));
	ret->win = mlx_new_window(ret->mlx, w, h, s);
	if (!ret->win)
		return (pcr_destroy_disp(ret));
	ret->img[0] = pcr_init_img(ret, w, h);
	if (!ret->img[0])
		return (pcr_destroy_disp(ret));
	ret->img[1] = pcr_init_img(ret, w, h);
	if (!ret->img[1])
		return (pcr_destroy_disp(ret));
	return (ret);
}

int	pcr_display(t_disp *d)
{
	//int				y;
	//int				x;
	//unsigned char	*dst;

	mlx_put_image_to_window(d->mlx, d->win, d->img[0 * d->frame % 2]->img, 0, 0);
	d->frame++;
	/*
	y = (d->frame + 1) % 2;
	while (y < d->h)
	{
		x = -1;
		while (++x < d->w)
			pcr_pixel(d, x, y, pcr_getpix(d->img[(d->frame - 1) % 2], x, y));
		y += 2;
	}
	*/
	/*
	while (++i < d->w * d->h)
	{
		dst = d->img[d->frame + 1 % 2]->addr + i * d->img[d->frame % 2]->opp;
		*(unsigned long *)dst = ;
	}
	*/
	return (0);
}
