/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/16 22:07:35 by lnr              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	draw_hud(t_cub *cub)
{
	t_pcrparam	p;

	p.cr1 = 0xffffff;
	p.x1 = WIN_W / 2;
	p.y1 = WIN_H / 2 - WIN_H / 100;
	p.y2 = WIN_H / 2 + WIN_H / 100;
	pcr_vline(cub->d, p);
	p.x1 = WIN_W / 2 - WIN_H / 100;
	p.x2 = WIN_W / 2 + WIN_H / 100;
	p.y1 = WIN_H / 2;
	pcr_hline(cub->d, p);
	return (0);
}

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
	draw_hud(cub);
	pcr_display(cub->d);
	return (0);
}

int	destroy_hook(t_disp *d)
{
	mlx_loop_end(d->mlx);
	return (0);
}

int	check_col(t_cub *cub, double x, double y)
{
	if (x < 0 || y < 0 || y >= cub->nbligne
		|| !cub->map[(int)y][(int)x] || cub->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

int	key_hook(int x, t_cub *cub)
{
	double	step_x;
	double	step_y;

	step_x = cub->or_cam[X] / 15;
	step_y = cub->or_cam[Y] / 15;
	if (x == KEY_RTL)
		cub->a += PI / 110;
	else if (x == KEY_RTR)
		cub->a -= PI / 110;
	else if (x == KEY_FWD)
	{
		if (!check_col(cub, cub->pos[X] + step_x, cub->pos[Y]))
			cub->pos[X] += step_x;
		if (!check_col(cub, cub->pos[X], cub->pos[Y] + step_y))
			cub->pos[Y] += step_y;
	}
	else if (x == KEY_BWD)
	{
		if (!check_col(cub, cub->pos[X] - step_x, cub->pos[Y]))
			cub->pos[X] -= step_x;
		if (!check_col(cub, cub->pos[X], cub->pos[Y] - step_y))
			cub->pos[Y] -= step_y;
	}
	else if (x == KEY_RSD)
	{
		if (!check_col(cub, cub->pos[X], cub->pos[Y] - step_y))
			cub->pos[X] -= step_y;
		if (!check_col(cub, cub->pos[X] + step_x, cub->pos[Y]))
			cub->pos[Y] += step_x;
	}
	else if (x == KEY_LSD)
	{
		if (!check_col(cub, cub->pos[X], cub->pos[Y] + step_y))
			cub->pos[X] += step_y;
		if (!check_col(cub, cub->pos[X] - step_x, cub->pos[Y]))
			cub->pos[Y] -= step_x;
	}
	else if (x == 'x' || x == KEY_ESC)
		mlx_loop_end(cub->d->mlx);
//	printf("%x %c\n", x, x);
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
	mlx_loop_hook(cub->d->mlx, &frame, cub);
	mlx_loop(cub->d->mlx);
	pcr_destroy_disp(cub->d);

	return (0);
}
