/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:47:24 by shamizi           #+#    #+#             */
/*   Updated: 2022/11/21 14:13:06 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	check_col(t_cub *cub, double x, double y)
{
	if (x < 0 || y < 0 || y >= cub->nbligne
		|| !cub->map[(int)y][(int)x] || cub->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	init_step(double *or_cam, double step[4][2], int sprint)
{
	step[0][0] = (1 + 0.5 * sprint) * or_cam[X] / 12;
	step[0][1] = (1 + 0.5 * sprint) * or_cam[Y] / 12;
	step[1][0] = -or_cam[X] / 12;
	step[1][1] = -or_cam[Y] / 12;
	step[2][0] = or_cam[Y] / 21;
	step[2][1] = -or_cam[X] / 21;
	step[3][0] = -or_cam[Y] / 21;
	step[3][1] = or_cam[X] / 21;
}

int	do_inputs(t_cub *cub)
{
	double	step[4][2];
	int		i;
	int		ret;

	init_step(cub->or_cam, step, cub->key_buffer[IDX_SPR]);
	ret = (cub->key_buffer[IDX_RTL] || cub->key_buffer[IDX_RTR]);
	cub->a += PI / 100 * (cub->key_buffer[IDX_RTL] - cub->key_buffer[IDX_RTR]);
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
