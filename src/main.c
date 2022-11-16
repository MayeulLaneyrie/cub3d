/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/16 12:36:46 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	frame(t_cub *cub)
{
	double	ray[2];
	t_hit	hit;
	int		x;

	cub->or_cam[0] = cos(cub->a);
	cub->or_cam[1] = sin(cub->a);
	cub->or_plancam[0] = cub->or_cam[1];
	cub->or_plancam[1] = -cub->or_cam[0];
	x = -1;
	while (++x < WIN_W)
	{
		ray[0] = cub->or_cam[0] + (-1 + 2 * x / WIN_W) * cub->or_plancam[0];
		ray[1] = cub->or_cam[1] + (-1 + 2 * x / WIN_W) * cub->or_plancam[1];
		hit = trace_ray(cub, ray);
		draw_hit(cub, hit, x);
	}
	pcr_display(cub->d);
	return (0);
}

int	destroy_hook(t_disp *d)
{
	mlx_loop_end(d->mlx);
	return (0);
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
		cub->posx, cub->posy, cub->pos[0], cub->pos[1]);
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
	mlx_loop_hook(cub->d->mlx, &frame, cub);
	mlx_loop(cub->d->mlx);
	pcr_destroy_disp(cub->d);

	return (0);
}
