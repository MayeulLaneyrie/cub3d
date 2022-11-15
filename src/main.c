/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/15 14:51:57 by mlaneyri         ###   ########.fr       */
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

int	expose_hook(t_disp *d)
{
	draw(d);
	return (0);
}

int	loop_hook(t_disp *d)
{
	draw(d);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;
	t_disp	*d;

	cub = malloc(sizeof(*cub));
	ft_init(cub);
	if (argc == 2)
		check_cub(argv[1], cub);
	else
		return (printf("Usage: ./cub3D FILE\n") - 1);

	d = pcr_init_disp(WIN_W, WIN_H, "Cub3D");
	if (!d)
		return (-2);
	mlx_hook(d->win, 17, 0L, &destroy_hook, d);
	mlx_hook(d->win, 12, 1L << 15, &expose_hook, d);
	mlx_loop_hook(d->mlx, &loop_hook, d);
	mlx_loop(d->mlx);
	pcr_destroy_disp(d);

	return (0);
}
