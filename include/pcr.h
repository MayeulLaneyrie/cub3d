/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:39:27 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/11/18 17:36:06 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PCR_H
# define PCR_H

# include <math.h>
# include <stdlib.h>
# include "mlx.h"

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		opp;
	int		w;
	int		endn;
	int		px_w;
	int		px_h;
}	t_image;

typedef struct s_disp
{
	int		frame;
	int		w;
	int		h;
	void	*mlx;
	void	*win;
	t_image	*img[2];
}	t_disp;

typedef struct s_pcrparam
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		cr1;
	int		cr2;
	char	*s;
	double	sin;
	double	cos;
}	t_pcrparam;

t_disp	*pcr_init_disp(int x, int y, char *s);

t_image	*pcr_load_img(void *mlx, char *s);

int		pcr_display(t_disp *d);

t_disp	*pcr_destroy_disp(t_disp *d);

int		pcr_getpix(t_image *img, int x, int y);
int		pcr_pixel(t_disp *d, int x, int y, int color);

int		abs(int x);
int		fsgn(double d);

int		pcr_fade(float t, int cr1, int cr2);

int		pcr_linefade(t_disp *d, t_pcrparam p);
int		pcr_line(t_disp *d, t_pcrparam p);

int		pcr_vline(t_disp *d, t_pcrparam p);
int		pcr_hline(t_disp *d, t_pcrparam p);

int		pcr_add(int cr1, int cr2);
int		pcr_mul(float x, int cr1);

#endif
