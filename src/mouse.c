/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnr <mayeul.lnr@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:57:28 by lnr               #+#    #+#             */
/*   Updated: 2022/11/23 21:03:11 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

#ifdef MOUSE_HIDE

int	mouse(t_disp *d, int action)
{
	if (action)
		mlx_mouse_show(d->mlx, d->win);
	else
		mlx_mouse_hide(d->mlx, d->win);
	return (0);
}

#else

int	mouse(t_disp *d, int action)
{
	return (0);
}

#endif
