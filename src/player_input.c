/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2023/01/25 19:05:33 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	check_col(t_cub *cub, double x, double y)
{
	if (!cub->bonus)
		return (0);
	if (x < 0 || y < 0 || y >= cub->mapsize[Y]
		|| (int)x > ft_strlen(cub->map[(int)y]))
		return (0);
	if (!cub->map[(int)y][(int)x] || cub->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	init_step(double *or_cam, double step[4][2], int sprint)
{
	int def;
   
	def = 64 * 2;
	step[0][0] = (1 + 0.5 * sprint) * or_cam[X] / def;
	step[0][1] = (1 + 0.5 * sprint) * or_cam[Y] / def;
	step[1][0] = -or_cam[X] / def;
	step[1][1] = -or_cam[Y] / def;
	step[2][0] = or_cam[Y] / (def * 21 / 12);
	step[2][1] = -or_cam[X] / (def * 21 / 12);
	step[3][0] = -or_cam[Y] / (def * 21 / 12);
	step[3][1] = or_cam[X] / (def * 21 / 12);
}

int	do_inputs(t_cub *cub)
{
	double	step[4][2];
	int		i;
	int		ret;

	if (cub->bonus > 1)
		return (0);
	init_step(cub->or_cam, step, cub->key_buffer[IDX_SPR]);
	ret = (cub->key_buffer[IDX_RTL] || cub->key_buffer[IDX_RTR]);
	cub->a += PI / (260 * 2) * (cub->key_buffer[IDX_RTL] - cub->key_buffer[IDX_RTR]);
	i = IDX_FWD - 1;
	while (++i <= IDX_RSD)
	{
		if (cub->key_buffer[i])
		{
			if (!check_col(cub, cub->pos[X] + step[i][X], cub->pos[Y]))
				cub->pos[X] += step[i][X];
			if (!check_col(cub, cub->pos[X], cub->pos[Y] + step[i][Y]))
				cub->pos[Y] += step[i][Y];
			ret = 1;
		}
	}
	return (ret);
}
