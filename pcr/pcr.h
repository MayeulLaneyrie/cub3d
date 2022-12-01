/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaneyri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:39:27 by mlaneyri          #+#    #+#             */
/*   Updated: 2022/12/01 18:35:19 by mlaneyri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PCR_H
# define PCR_H

# include <math.h>
# include <stdlib.h>
# include "mlx.h"

/*
**	POLYCHROME v2022.12.01, by Mayeul 'mlaneyri' Laneyrie
*/

/*
**	Polychrome(PCR) is a simple interface that makes using minilibX much easier,
**	PCR allows you to use the mlx in a most optimal way, without having to worry
**	about managing boring stuff like mlx images setup, buffering or a lot of
**	bitwise stuff.
**
**	To start using pcr:
**
**		t_disp	*d;
**		d = pcr_init_disp(win_width, win_height, "win_title");
**
**	Will return a pointer to a t_disp structure, that will serve as the only
**	handler you'll need as a display. No need to juggle with a mlx_ptr and a
**	separate win_ptr.
**
**	It is of your responsibility to free the allocated resources by calling:
**
**		pcr_destroy_disp(d);
**
**	at the end of your program.
**	Much of the drawing process could be summed up to:
**
**		pcr_pixel(x, y, color);
**
**	Please note that this function will NOT update the window, as the pcr
**	implement natively a double-buffering system. Any pixel will first
**	be written to an image buffer, that you can display to the window (once
**	your frame is ready) by using:
**
**		pcr_display(d);
**
**	In order to conform to the commands of the most holy **NORM** regarding the
**	number of parameters a function can take, all drawing function take a
**	't_pcrparam' as parameter. This structure will contain all the values
**	required by the function. Here's a quick example :
**
**		t_disp		*d;
**		t_pcrparam	p;
**
**		d = pcr_init(1280, 720, "Hello, world!");
**		if (!d)
**			some_kind_of_error_management_i_guess(...);
**		p.x1 = 42;
**		p.y1 = 69;
**		p.x2 = 987;
**		p.y2 = 500;
**		p.cr1 = 0x177013;
**		pcr_line(d, p);
**
**	will draw a greenish line between points (42, 69) & (500, 987).
*/

typedef struct s_image
{
	void			*img;
	unsigned char	*addr;
	int				bpp;
	int				opp;
	int				w;
	int				endn;
	int				px_w;
	int				px_h;
}	t_image;

/*
**	frame	:	the number of frames that have been displayed. Updated at each
**	w		:	width in pixels.							pcr_display() call.
**	h		:	height in pixels.
**	*mlx	:	mlx pointer.
**	*win	:	window pointer.
**	*img[2]	:	the two images used as buffers, the current being img[frame % 2]
*/
typedef struct s_disp
{
	int		frame;
	int		w;
	int		h; 
	void	*mlx;
	void	*win;
	t_image	*img[2];
}	t_disp;

/*
**	The meaning of all those is pretty much contextual and may vary according to
**	the function you're giving a t_pcrparam as parameter, please refer to the
**	specific documentation of each drawing function. Not all members will be
**	systematically used.
**
**	However, you can be quite confident in the fact that:
**		- (x1, y1) will represent a starting position,
**		- (x2, y2) will represent an ending position,
**		- cr1 & cr2 will represent colors,
**		- *s will represent a string to be displayed.
*/
typedef struct s_pcrparam
{
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		cr1;
	int		cr2;
	char	*s;
}	t_pcrparam;

/*
**	pcr_init.c: ----------------------------------------------------------------
*/

/*
**	Initializes all we need, open a window of w*h pixels titled s.
**	Returns a t_disp * to our display, or NULL in case of failure.
*/
t_disp	*pcr_init_disp(int w, int h, char *s);

/*
**	Creates an image of w*h pixels we'll be able to use within the display d.
**	Returns a t_image * to our image, or NULL in case in case of failure.
*/
t_image	*pcr_init_img(t_disp *d, int w, int h);

/*
**	Loads the .xpm file located at s as an image.
**	Returns a t_image * to our image, or NULL in case of failure.
*/
t_image	*pcr_load_img(t_disp *d, char *s);

/*
**	Display the current image buffer to window. The previous image buffer is
**	then cleaned and will be used as the next image buffer.
**	Returns 0.
*/
int		pcr_display(t_disp *d);

/*
**	pcr_destroy.c: -------------------------------------------------------------
*/

/*
**	Frees all the resources associated to img, returns NULL.
*/
t_image	*pcr_destroy_img(t_disp *d, t_image *img);

/*
**	Closes the display d, frees all its resources, returns NULL.
*/
t_disp	*pcr_destroy_disp(t_disp *d);

/*
**	pcr_ops.c: -----------------------------------------------------------------
*/

int		abs(int x);
int		fsgn(double d);
int		pcr_fade(float t, int cr1, int cr2);
int		pcr_add(int cr1, int cr2);
int		pcr_mul(float x, int cr1);

/*
**	pcr_pixel.c: ---------------------------------------------------------------
*/

/*
**	Returns the color of the pixel (x, y) in image img.
*/
int		pcr_getpix(t_image *img, int x, int y);

/*
**	Set the color of the pixel (x, y) to color in the current image buffer.
*/
int		pcr_pixel(t_disp *d, int x, int y, int color);

/*
**	Same as pcr_pixel but manages transparency. The bits to use for transparency
**	are defined by the mask 0xff000000. Usage of this function is quite slow, so
**	use it only when transparency is required.
*/
int		pcr_pixel_alpha(t_disp *d, int x, int y, int color);

/*
** 	pcr_rect.c: ----------------------------------------------------------------
*/

/*
**	Draws a filled rectangle:
**		- (x1, y1): straing point (included),
**		- (x2, y2): width & height,
**		- cr1: the color of the rectangle.
*/
int		pcr_rect(t_disp *d, t_pcrparam p);

/*
**	pcr_txt.c: -----------------------------------------------------------------
**
**	Due to the way the mlx manages text, all those functions will have to be
**	called SUBSEQUENTLY to a call to pcr_disp(). Sorry :'-(
**
**	PCR text management is still in an early stage. You'll have to set the font
**	using mlx_set_font. Knowing which font can be used is another tricky part.
**	See XListFonts().
**
**	No documentation will be provided on this matter, by lack of time.
**	Once again, sorry :'-(
*/
int		pcr_txt(t_disp *d, t_pcrparam p);
int		pcr_txt_shadow(t_disp *d, t_pcrparam p);

/*
**	pcr_line.h:	----------------------------------------------------------------
*/

/*
**	Draws a line, using a bresenham algorithm:
**		- (x1, y1): starting point (included),
**		- (x1, y2)): ending point (included),
**		- cr1: color.
*/
int		pcr_line(t_disp *d, t_pcrparam p);

/*
**	Does the same as pcr_line, but the line will be faded between two colors
**	defined by cr1 & cr2. Much useful for a stylish fdf.
*/
int		pcr_linefade(t_disp *d, t_pcrparam p);

/*
**	pcr_vhline.h: --------------------------------------------------------------
*/
int		pcr_vline(t_disp *d, t_pcrparam p);
int		pcr_hline(t_disp *d, t_pcrparam p);

#endif
