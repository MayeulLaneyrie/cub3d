/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:33:07 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/18 17:34:13 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pcr.h"

t_image	*pcr_init_img(void *mlx, int x, int y)
{
	t_image	*ret;

	ret = malloc(sizeof(t_image));
	if (!ret)
		return (NULL);
	ret->img = mlx_new_image(mlx, x, y);
	ret->addr = mlx_get_data_addr(ret->img, &(ret->bpp), &(ret->w),
			&(ret->endn));
	ret->opp = ret->bpp / 8;
	ret->px_w = x;
	ret->px_h = y;
	return (ret);
}

t_disp	*pcr_init_disp(int x, int y, char *s)
{
	t_disp	*ret;

	ret = malloc(sizeof(t_disp));
	if (!ret)
		return (NULL);
	ret->frame = 0;
	ret->w = x;
	ret->h = y;
	ret->img[0] = NULL;
	ret->img[1] = NULL;
	ret->win = NULL;
	ret->mlx = mlx_init();
	if (!ret->mlx)
		return (pcr_destroy_disp(ret));
	ret->win = mlx_new_window(ret->mlx, x, y, s);
	if (!ret->win)
		return (pcr_destroy_disp(ret));
	ret->img[0] = pcr_init_img(ret->mlx, x, y);
	if (!ret->img[0])
		return (pcr_destroy_disp(ret));
	ret->img[1] = pcr_init_img(ret->mlx, x, y);
	if (!ret->img[1])
		return (pcr_destroy_disp(ret));
	return (ret);
}

int	pcr_display(t_disp *d)
{
	int		i;
	char	*dst;

	mlx_put_image_to_window(d->mlx, d->win, d->img[d->frame % 2]->img, 0, 0);
	d->frame++;
	i = -1;
	while (++i < d->w * d->h)
	{
		dst = d->img[d->frame % 2]->addr + i * d->img[d->frame % 2]->opp;
		*(unsigned long *)dst = 0;
	}
	return (0);
}

t_disp	*pcr_destroy_disp(t_disp *d)
{
	if (!d)
		return (NULL);
	if (d->img[0])
		mlx_destroy_image(d->mlx, d->img[0]->img);
	free(d->img[0]);
	if (d->img[1])
		mlx_destroy_image(d->mlx, d->img[1]->img);
	free(d->img[1]);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
		mlx_destroy_display(d->mlx);
	free(d->mlx);
	free(d);
	return (NULL);
}

t_image	*pcr_load_img(void *mlx, char *path)
{
	t_image	*ret;

	ret = malloc(sizeof(t_image));
	if (!ret)
		return (NULL);
	ret->img = mlx_xpm_file_to_image(mlx, path, &(ret->px_w), &(ret->px_h));
	if (!ret->img)
	{
		free(ret);
		return (NULL);
	}
	ret->addr = mlx_get_data_addr(ret->img, &(ret->bpp), &(ret->w),
			&(ret->endn));
	ret->opp = ret->bpp / 8;
	return (ret);
}
