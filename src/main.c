/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/21 13:52:56 by mlaneyri         ###   ########.fr       */
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
	{
		free_cub(&cub);
		return (-2);
	}
	texture_check(&cub);
	mlx_hook(cub.d->win, 17, 0L, &destroy_hook, cub.d);
	mlx_hook(cub.d->win, 12, 1L << 15, &frame, &cub);
	mlx_hook(cub.d->win, 2, 1L << 0, &key_hook, &cub);
	mlx_hook(cub.d->win, 3, 1L << 1, &release_hook, &cub);
	//mlx_mouse_hide(cub.d->mlx, cub.d->win);
	//mlx_hook(cub.d->win, 6, 1L << 6, &mouse_motion_hook, &cub);
	mlx_loop_hook(cub.d->mlx, &loop_hook, &cub);
	mlx_loop(cub.d->mlx);
	free_cub(&cub);
	pcr_destroy_disp(cub.d);
	return (0);
}
