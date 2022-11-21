/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr_line_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:34:23 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/21 17:46:00 by mlaneyri         ###   ########.fr       */
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
