/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/23 12:28:51 by mlaneyri         ###   ########.fr       */
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
	static const int	keybufftable[7]
		= {KEY_FWD, KEY_BWD, KEY_LSD, KEY_RSD, KEY_RTL, KEY_RTR, KEY_SPR};
	int					i;

	i = -1;
	while (++i < 7)
		if (keybufftable[i] == x)
			cub->key_buffer[i] = 1;
	if (x == 'x' || (x == KEY_ESC && !cub->bonus))
		mlx_loop_end(cub->d->mlx);
	if (x == KEY_ESC && cub->bonus)
	{
		cub->bonus = 1 + (cub->bonus == 1);
		frame(cub);
	}
	return (0);
}

/*
**	@33:
**		if (cub->bonus == 1)
**			mlx_mouse_hide(cub->d->mlx, cub->d->win);
*/

int	release_hook(int x, t_cub *cub)
{
	static const int	keybufftable[7]
		= {KEY_FWD, KEY_BWD, KEY_LSD, KEY_RSD, KEY_RTL, KEY_RTR, KEY_SPR};
	int					i;

	i = -1;
	while (++i < 7)
		if (keybufftable[i] == x)
			cub->key_buffer[i] = 0;
	return (0);
}

int	mouse_motion_hook(int x, int y, t_cub *cub)
{
	static int	not_first = 0;

	(void)y;
	if (x == WIN_W / 2 || cub->bonus > 1)
		return (0);
	if (not_first > 5)
		cub->a += (WIN_W / 2 - x) * PI / 6000;
	else
		not_first++;
	mlx_mouse_move(cub->d->mlx, cub->d->win, WIN_W / 2, WIN_H / 2);
	cub->update = 1;
	return (0);
}

int	loop_hook(t_cub *cub)
{
	if (do_inputs(cub))
		frame(cub);
	else if (cub->update)
	{
		frame(cub);
		cub->update = 0;
	}
	return (0);
}
