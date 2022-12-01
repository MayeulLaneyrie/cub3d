/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:34:23 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/12/01 17:08:57 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pcr.h"

int	abs(int x)
{
	if (x > 0)
		return (x);
	return (-x);
}

int	fsgn(double d)
{
	if (d < 0)
		return (-1);
	return (1);
}

int	pcr_fade(float t, int cr1, int cr2)
{
	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	return (pcr_add(pcr_mul(1 - t, cr1), pcr_mul(t, cr2)));
}

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
