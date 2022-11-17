/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/17 18:19:56 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	destroy_hook(t_disp *d)
{
	mlx_loop_end(d->mlx);
	return (0);
}

int	key_hook(int x, t_cub *cub)
{
	static const int	keybufftable[6]
		= {KEY_FWD, KEY_BWD, KEY_LSD, KEY_RSD, KEY_RTL, KEY_RTR};
	int					i;

	i = -1;
	while (++i < 6)
		if (keybufftable[i] == x)
			cub->key_buffer[i] = 1;
	if (x == 'x' || x == KEY_ESC)
		mlx_loop_end(cub->d->mlx);
	return (0);
}

int	release_hook(int x, t_cub *cub)
{
	static const int	keybufftable[6]
		= {KEY_FWD, KEY_BWD, KEY_LSD, KEY_RSD, KEY_RTL, KEY_RTR};
	int					i;

	i = -1;
	while (++i < 6)
		if (keybufftable[i] == x)
			cub->key_buffer[i] = 0;
	return (0);
}

int	mouse_motion_hook(int x, int y, t_cub *cub)
{
	(void)y;
	cub->a += (WIN_W / 2 - x) * PI / 8000;
	mlx_mouse_move(cub->d->mlx, cub->d->win, WIN_W / 2, WIN_H / 2);
	return (0);
}

int	loop_hook(t_cub *cub)
{
	do_inputs(cub);
	frame(cub);
	return (0);
}
