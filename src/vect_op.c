/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <mlaneyri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:03:08 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/15 16:26:15 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub.h"

int	add_v(double const *u, double const *v, double *dst)
{
	dst[0] = u[0] + v[0];
	dst[1] = u[1] + v[1];
	return (0);
}

int	sub_v(double const *u, double const *v, double *dst)
{
	dst[0] = u[0] - v[0];
	dst[1] = u[1] - v[1];
	return (0);
}

int	mul_rv(double t, double const *u, double *dst)
{
	dst[0] = t * u[0];
	dst[1] = t * u[1];
	return (0);
}
