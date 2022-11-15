/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_color_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:02:12 by mlaneyri          #+#    #+#             */
/*   Updated: 2021/12/22 18:39:06 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pcr.h"

int	pcr_add(int cr1, int cr2)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = (cr1 >> 24) + (cr2 >> 24);
	if (a > 0xff)
		a = 0xff;
	r = ((cr1 >> 16) & 0xff) + ((cr2 >> 16) & 0xff);
	if (r > 0xff)
		r = 0xff;
	g = ((cr1 >> 8) & 0xff) + ((cr2 >> 8) & 0xff);
	if (g > 0xff)
		g = 0xff;
	b = (cr1 & 0xff) + (cr2 & 0xff);
	if (b > 0xff)
		b = 0xff;
	return ((a << 24) + (r << 16) + (g << 8) + b);
}

int	pcr_mul(float x, int cr1)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = x * (cr1 >> 24);
	if (a > 0xff)
		a = 0xff;
	r = x * ((cr1 >> 16) & 0xff);
	if (r > 0xff)
		r = 0xff;
	g = x * ((cr1 >> 8) & 0xff);
	if (g > 0xff)
		g = 0xff;
	b = x * (cr1 & 0xff);
	if (b > 0xff)
		b = 0xff;
	return ((a << 24) + (r << 16) + (g << 8) + b);
}
