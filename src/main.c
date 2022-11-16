/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/16 17:16:47 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	frame(t_cub *cub)
{
	double	ray[2];
	t_hit	hit;
	int		x;

	cub->or_cam[X] = cos(cub->a);
	cub->or_cam[Y] = -sin(cub->a);
	cub->or_plancam[X] = -cub->or_cam[Y];
	cub->or_plancam[Y] = cub->or_cam[X];
	x = 0;
	while (x < WIN_W)
	{
		ray[X] = cub->or_cam[X] + (-1.0 + 2.0 * x / WIN_W) * cub->or_plancam[0];
		ray[Y] = cub->or_cam[Y] + (-1.0 + 2.0 * x / WIN_W) * cub->or_plancam[1];
		trace_ray(cub, ray, &hit);
		draw_hit(cub, hit, x);
		x += 1;
	}
	pcr_display(cub->d);
	return (0);
}

int	destroy_hook(t_disp *d)
{
	mlx_loop_end(d->mlx);
	return (0);
}

int	key_hook(int x, t_cub *cub)
{
	if (x == 0xff51)
		cub->a += PI / 120;
	else if (x == 0xff53)
		cub->a -= PI / 120;
	else if (x == 0x77)
	{
		cub->pos[X] += cub->or_cam[X] / 20;
		cub->pos[Y] += cub->or_cam[Y] / 20;
	}
	else if (x == 0x73)
	{
		cub->pos[X] -= cub->or_cam[X] / 20;
		cub->pos[Y] -= cub->or_cam[Y] / 20;
	}
	else if (x == 0x64)
	{
		cub->pos[X] -= cub->or_cam[Y] / 20;
		cub->pos[Y] += cub->or_cam[X] / 20;
	}
	else if (x == 0x61)
	{
		cub->pos[X] += cub->or_cam[Y] / 20;
		cub->pos[Y] -= cub->or_cam[X] / 20;
	}
	else if (x == 0x78)
		mlx_loop_end(cub->d->mlx);
	return (frame(cub));
}

int	debug_cub(t_cub *cub)
{
	printf("%d lines\n\n", cub->nbligne);
	for (int i = 0; i < cub->nbligne; i++)
		printf("%s\n", cub->map[i]);
	printf("\nNO: %s\nSO: %s\nEA: %s\nWE: %s\n\n",
		cub->no, cub->so, cub->ea, cub->we);
	printf("C: %x; F: %x\n\n", cub->c, cub->f);
	printf("posx: %f; posy: %f\npos[0]: %f; pos[1]: %f\n",
		cub->pos[X], cub->pos[Y], cub->pos[0], cub->pos[1]);
	cub->a = PI / 3;
	printf("a: %f\n", cub->a);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = malloc(sizeof(*cub));
	ft_init(cub);
	if (argc == 2)
		check_cub(argv[1], cub);
	else
		return (printf("Usage: ./cub3D FILE\n") - 1);

	debug_cub(cub);

	cub->d = pcr_init_disp(WIN_W, WIN_H, "Cum3D");
	if (!cub->d)
		return (-2);
	mlx_hook(cub->d->win, 17, 0L, &destroy_hook, cub->d);
	mlx_hook(cub->d->win, 12, 1L << 15, &frame, cub);
	mlx_hook(cub->d->win, 2, 1L << 0, &key_hook, cub);
	mlx_loop(cub->d->mlx);
	pcr_destroy_disp(cub->d);

	return (0);
}
