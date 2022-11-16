/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:36:56 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/16 11:41:16 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

t_hit	trace_ray(t_cub *cub, double *ray)
{
	t_hit	ret;

	(void)cub;
	(void)ray;

	ret.dist = 1;
	ret.face = no;
	return (ret);
}
