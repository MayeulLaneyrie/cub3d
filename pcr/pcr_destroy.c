/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:33:07 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/21 13:49:55 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pcr.h"

t_image	*pcr_destroy_img(t_disp *d, t_image *img)
{
	if (!d)
		return (NULL);
	if (img)
		mlx_destroy_image(d->mlx, img->img);
	free(img);
	return (NULL);
}

t_disp	*pcr_destroy_disp(t_disp *d)
{
	if (!d)
		return (NULL);
	pcr_destroy_img(d, d->img[0]);
	pcr_destroy_img(d, d->img[1]);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
		mlx_destroy_display(d->mlx);
	free(d->mlx);
	free(d);
	return (NULL);
}
