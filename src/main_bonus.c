/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/23 21:32:05 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (printf("Usage: ./cub3D FILE\n") - 1);
	ft_init(&cub);
	check_cub(argv[1], &cub);
	cub.d = pcr_init_disp(WIN_W, WIN_H, "Cum3D");
	if (!cub.d)
		return (free_cub(&cub) - 2);
	cub.bonus = 1;
	texture_check(&cub);
	mlx_set_font(cub.d->mlx, cub.d->win, "12x24");
	mlx_hook(cub.d->win, 17, 0L, &destroy_hook, cub.d);
	mlx_hook(cub.d->win, 12, 1L << 15, &frame, &cub);
	mlx_hook(cub.d->win, 2, 1L << 0, &key_hook, &cub);
	mlx_hook(cub.d->win, 3, 1L << 1, &release_hook, &cub);
	mlx_hook(cub.d->win, 6, 1L << 6, &mouse_motion_hook, &cub);
	mlx_loop_hook(cub.d->mlx, &loop_hook, &cub);
	mouse(cub.d, 0);
	mlx_loop(cub.d->mlx);
	free_cub(&cub);
	pcr_destroy_disp(cub.d);
	return (0);
}

/*
**	@35:
**	mlx_mouse_hide(cub.d->mlx, cub.d->win);
*/
