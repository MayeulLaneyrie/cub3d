/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/15 17:24:26 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	draw(t_disp *d)
{
	static double	var = 0.01;
	static double	t = 0;
	int				n;
	int				p;

	n = 0;
	while (n < WIN_H)
	{
		p = n % 2;
		while (p < WIN_W)
		{
			pcr_pixel(d, p, n, pcr_fade(t, 0xff0000, 0x0000ff));
			p += 8;
		}
		n++;
	}
	t += var;
	if (t > 1 || t < 0)
		var = -var;
	pcr_display(d);
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
	mlx_hook(cub->d->win, 12, 1L << 15, &draw, cub->d);
	mlx_loop_hook(cub->d->mlx, &draw, cub->d);
	mlx_loop(cub->d->mlx);
	pcr_destroy_disp(cub->d);

	return (0);
}
